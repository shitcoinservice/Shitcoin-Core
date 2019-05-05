Sample init scripts and service configuration for shitcoind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/shitcoind.service:    systemd service unit configuration
    contrib/init/shitcoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/shitcoind.openrcconf: OpenRC conf.d file
    contrib/init/shitcoind.conf:       Upstart service configuration file
    contrib/init/shitcoind.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three startup configurations assume the existence of a "shitcoin" user
and group.  They must be created before attempting to use these scripts.

2. Configuration
---------------------------------

At a bare minimum, shitcoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, shitcoind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that shitcoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If shitcoind is run with "-daemon" flag, and no rpcpassword is set, it will
print a randomly generated suitable password to stderr.  You can also
generate one from the shell yourself like this:

bash -c 'tr -dc a-zA-Z0-9 < /dev/urandom | head -c32 && echo'

Once you have a password in hand, set rpcpassword= in /etc/shitcoin/shitcoin.conf

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/shitcoin.conf.

3. Paths
---------------------------------

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/shitcoind
Configuration file:  /etc/shitcoin/shitcoin.conf
Data directory:      /var/lib/shitcoind
PID file:            /var/run/shitcoind/shitcoind.pid (OpenRC and Upstart)
                     /var/lib/shitcoind/shitcoind.pid (systemd)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the shitcoin user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
shitcoin user and group.  Access to shitcoin-cli and other shitcoind rpc clients
can then be controlled by group membership.

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists on just copying it to
/usr/lib/systemd/system directory, followed by the command
"systemctl daemon-reload" in order to update running systemd configuration.

To test, run "systemctl start shitcoind" and to enable for system startup run
"systemctl enable shitcoind"

4b) OpenRC

Rename shitcoind.openrc to shitcoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
"/etc/init.d/shitcoind start" and configure it to run on startup with
"rc-update add shitcoind"

4c) Upstart (for Debian/Ubuntu based distributions)

Drop shitcoind.conf in /etc/init.  Test by running "service shitcoind start"
it will automatically start on reboot.

4d) CentOS

Copy shitcoind.init to /etc/init.d/shitcoind. Test by running "service shitcoind start".

Using this script, you can adjust the path and flags to the shitcoind program by
setting the ShitcoinD and FLAGS environment variables in the file
/etc/sysconfig/shitcoind. You can also use the DAEMONOPTS environment variable here.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
