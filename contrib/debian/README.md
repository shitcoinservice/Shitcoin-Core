
Debian
====================
This directory contains files used to package shitcoind/shitcoin-qt
for Debian-based Linux systems. If you compile shitcoind/shitcoin-qt yourself, there are some useful files here.

## shitcoin: URI support ##


shitcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install shitcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your shitcoinqt binary to `/usr/bin`
and the `../../share/pixmaps/shitcoin128.png` to `/usr/share/pixmaps`

shitcoin-qt.protocol (KDE)

