Shitcoin Core V1.0.0
=====================

Setup
---------------------
[Shitcoin Core](http://www.shitcoin.cash) is the original Shitcoin client and it builds the backbone of the network. However, it downloads and stores the entire history of Shitcoin transactions; depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once.

Running
---------------------
The following are some helpful notes on how to run Shitcoin on your native platform.

### Unix

Unpack the files into a directory and run:

- bin/32/shitcoin-qt (GUI, 32-bit) or bin/32/shitcoind (headless, 32-bit)
- bin/64/shitcoin-qt (GUI, 64-bit) or bin/64/shitcoind (headless, 64-bit)

### Windows

Unpack the files into a directory, and then run shitcoin-qt.exe.

### OSX

Drag Shitcoin-Qt to your applications folder, and then run Shitcoin-Qt.

### Need Help?

* [Shitcoin Wiki] ***TODO***
* [BitcoinTalk] **TODO**
* [Shitcoin Forum] **TODO**
* [Shitcoin Discord Groups] **TODO**

Building
---------------------
The following are developer notes on how to build Shitcoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](BUILD-OSX.md)
- [Unix Build Notes](BUILD-UNIX.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Shitcoin repo's [root README](https://github.com/Shitcoinservice/Shitcoin-Core/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Dnsseed Policy](dnsseed-policy.md)


### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
