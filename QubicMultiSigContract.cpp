#include <qubic/core/crypto.hpp>
#include <qubic/core/data.hpp>
#include <qubic/core/exceptions.hpp>

using namespace qubic;

/**
 * MultiSigWallet class represents a multi-signature wallet contract
 */
class MultiSigWallet {
public:
    /**
     * Constructor initializes the owner and required signatures
     * @param owner The owner of the wallet
     * @param requiredSignatures The number of required signatures
     */
    MultiSigWallet(Address owner, uint256 requiredSignatures) 
        : owner_(owner), requiredSignatures_(requiredSignatures), authorizedSigners_() {}

    /**
     * Checks if the wallet has sufficient balance for a transaction
     * @param amount The amount to check
     * @return True if the balance is sufficient, false otherwise
     */
    bool hasSufficientBalance(uint256 amount) {
        Balance balance = getBalance();
        if (balance < 0) {
            revert("Error: Negative balance");
        }
        return balance >= amount;
    }

    /**
     * Verifies a list of signatures
     * @param signatures The list of signatures to verify
     * @return True if the signatures are valid, false otherwise
     */
    bool verifySignatures(std::vector<Signature> signatures) {
        for (auto& signature : signatures) {
            Address signer = signature.getAddress();
            if (!authorizedSigners_.count(signer)) {
                revert("Error: Unauthorized signer");
            }
            if (!crypto::verifySignature(signature, authorizedSigners_[signer])) {
                return false;
            }
        }
        return signatures.size() >= requiredSignatures_;
    }

    /**
     * Executes a transaction if the signatures are valid and the balance is sufficient
     * @param recipient The recipient of the transaction
     * @param amount The amount of the transaction
     * @param signatures The list of signatures
     */
    void executeTransaction(Address recipient, uint256 amount, std::vector<Signature> signatures) {
        if (!hasSufficientBalance(amount)) {
            revert("Insufficient balance");
        }
        if (!verifySignatures(signatures)) {
            revert("Invalid signatures");
        }
        if (!isValidRecipient(recipient)) {
            revert("Error: Invalid recipient");
        }
        if (amount <= 0) {
            revert("Error: Invalid amount");
        }
        Transaction tx = createTransaction(recipient, amount);
        broadcastTransaction(tx);
        updateBalance(-amount);
    }

    /**
     * Adds an authorized signer to the wallet
     * @param signer The address of the signer
     * @param publicKey The public key of the signer
     */
    void addAuthorizedSigner(Address signer, PublicKey publicKey) {
        authorizedSigners_[signer] = publicKey;
    }

    /**
     * Removes an authorized signer from the wallet
     * @param signer The address of the signer
     */
    void removeAuthorizedSigner(Address signer) {
        authorizedSigners_.erase(signer);
    }

    /**
     * Updates the required signatures for the wallet
     * @param requiredSignatures The new required signatures
     */
    void updateRequiredSignatures(uint256 requiredSignatures) {
        requiredSignatures_ = requiredSignatures;
    }

private:
    /**
     * The owner of the wallet
     */
    Address owner_;

    /**
     * The number of required signatures
     */
    uint256 requiredSignatures_;

    /**
     * The map of authorized signers and their public keys
     */
    std::map<Address, PublicKey> authorizedSigners_;

    /**
     * Gets the balance of the wallet
     * @return The balance of the wallet
     */
    Balance getBalance() {
        return storage::getBalance(owner_);
    }

    /**
     * Gets the public key of a signer
     * @param signer The address of the signer
     * @return The public key of the signer
     */
    PublicKey getSignerPublicKey(Address signer) {
        if (!authorizedSigners_.count(signer)) {
            revert("Error: Unauthorized signer");
        }
        return authorizedSigners_[signer];
    }

    /**
     * Creates a new transaction
     * @param recipient The recipient of the transaction
     * @param amount The amount of the transaction
     * @return The new transaction
     */
    Transaction createTransaction(Address recipient, uint256 amount) {
        Transaction tx;
        tx.setRecipient(recipient);
        tx.setAmount(amount);
        return tx;
    }

    /**
     * Broadcasts a transaction to the network
     * @param tx The transaction to broadcast
     */
    void broadcastTransaction(Transaction tx) {
        network::broadcastTransaction(tx);
    }

    /**
     * Updates the balance of the wallet
     * @param amount The amount to update the balance by
     */
    void updateBalance(int256 amount
