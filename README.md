# MultiSigQ: Qubic Network Multi-Signature Wallet Contract (DRAFT)
=====================================================

![MultiSigQ Logo](https://github.com/qudeveloper/MultiSigQ/blob/main/logo.jpg)

[![Draft](https://img.shields.io/badge/Draft-UNOFFICIAL-red.svg)]() Disclaimer This repository is a draft and not officially endorsed, but it can be used as a boilerplate for your projects. Feel free to use it as is, but please note that it may not be fully polished or tested.

**Introduction**
===============

This repository contains a multi-signature wallet contract for the Qubic network, a decentralized platform for building scalable and secure applications. The contract allows multiple parties to jointly manage a wallet, requiring a minimum number of signatures to authorize transactions.

**Functionality**
===============

### Multi-Signature Wallet

* Create a multi-signature wallet with a minimum number of required signatures
* Add and manage multiple owners and their corresponding public keys
* Set the minimum number of required signatures for transactions
* Authorize transactions with multiple signatures

### Security Features

* Implement secure multi-party computation to protect sensitive data
* Use advanced cryptographic algorithms to ensure the integrity of transactions

**Installation**
==============

### Prerequisites

* Qubic network node (version 1.0 or higher)

### Building and Deploying the Contract

* Clone the repository: `git clone https://github.com/qudeveloper/MultiSigQ.git`
* Install dependencies: `npm install`
* Compile the contract: `npx qubic-compiler compile QubicMultiSigContract.cpp`
* Deploy the contract: `npx qubic-deploy deploy QubicMultiSigContract.bin`

**Usage**
=======

### Creating a Multi-Signature Wallet

* Create a new wallet: `npx qubic-cli create-wallet --owners <owner1>,<owner2>,... --required-signatures <min-signatures>`
* Add owners and set the minimum number of required signatures: `npx qubic-cli update-wallet --owners <owner1>,<owner2>,... --required-signatures <min-signatures>`

### Authorizing Transactions

* Create a new transaction: `npx qubic-cli create-transaction --from <wallet-address> --to <recipient-address> --amount <amount>`
* Sign the transaction: `npx qubic-cli sign-transaction --transaction-id <transaction-id> --owner <owner-address>`
* Authorize the transaction: `npx qubic-cli authorize-transaction --transaction-id <transaction-id> --signatures <signature1>,<signature2>,...`

**Contract Functions and Procedures**
=====================================

### Initialize

* Initializes the contract with the required number of signatures and resets the authorized signers collection.

### HasSufficientBalance

* Checks if the balance is sufficient for a transaction.

### VerifySignatures

* Verifies the signatures of a transaction.

### ExecuteTransaction

* Executes a transaction if the balance is sufficient and the signatures are valid.

### AddAuthorizedSigner

* Adds a new authorized signer to the collection.

### RemoveAuthorizedSigner

* Removes an authorized signer from the collection.

### UpdateRequiredSignatures

* Updates the required number of signatures.

**License**
=========

This project is licensed under the AGPL-3.0 license.

**Contributing**
===============

Contributions are welcome! Please open a pull request to submit changes or bug fixes.

**Acknowledgments**
================

This project is built on top of the Qubic network and utilizes its decentralized infrastructure. We would like to thank the Qubic team for their support and contributions to the ecosystem.

**Contact**
=========

For questions, issues, or feedback, please contact us at qumarketingadmin@proton.me
