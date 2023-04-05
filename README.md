# Mini Signalized Intersection Source Code

## Components

### SIGNALCONTROLLERMAIN

The `signalcontrollermain` components contains the logic for the signal controller, which runs on the main Arduino
device.

#### Hardware Requirements

* [\(x1\) Automation Direct ProductivityOpen Arduino-Compatible PLC \(P1AM-100\)](https://www.automationdirect.com/adc/shopping/catalog/programmable_controllers/productivity_open_(arduino-compatible)/controllers_-a-_shields/p1am-100)
    * [\(x1\) Automation Direct Productivity1000 AC\/DC Power Supply \(P1-01AC\)](https://www.automationdirect.com/adc/shopping/catalog/programmable_controllers/productivity_open_(arduino-compatible)/power_supplies/p1-01ac)
    * [\(x1\) Automation Direct ProductivityOpen Ethernet Shield \(P1AM-ETH\)](https://www.automationdirect.com/adc/shopping/catalog/programmable_controllers/productivity_open_(arduino-compatible)/controllers_-a-_shields/p1am-eth)
    * [\(x1\) Automation Direct ProductivityOpen General Purpose I/O Shield \(P1AM-GPIO\)](https://www.automationdirect.com/adc/shopping/catalog/programmable_controllers/productivity_open_(arduino-compatible)/controllers_-a-_shields/p1am-gpio)
    * [\(x2\) Automation Direct Productivity1000 8-Point 120-240 VAC Discrete Output Module \(P1-08TA\)](https://www.automationdirect.com/adc/shopping/catalog/programmable_controllers/productivity1000_plcs_(stackable_micro)/ac_i-z-o/p1-08ta)

#### Software Requirements

The PLC program must be compiled using the [Arduino IDE](https://www.arduino.cc/en/software) and the ProductivityOpen
PLC library.

Information about configuring the Arduino IDE to compile ProductivityOpen PLC programs can be found on the Facts
Engineering ProductivityOpen Webpage,
[https://facts-engineering.github.io/](https://facts-engineering.github.io/).

The following additional dependent libraries must also be installed:

* aWOT (`aWOT.h`, available in the Arduino IDE Library Manager)
* SPI (`SPI.h`, available in the Arduino IDE Library Manager)
* Ethernet (`Ethernet.h`, available in the Arduino IDE Library Manager)

#### Configuration

##### Networking

A static IP address is required for the PLC to communicate with the Raspberry Pi hosting the `signalcontrollerwebui`
component.

The default IP address assigned is `10.0.0.1` (IP address of PLC), and the default gateway + DNS server is `10.0.0.2`
(IP address of Raspberry Pi). If desired, these values may be modified in the `signalcontrollermain.ino` file.

### SIGNALCONTROLLERWEBUI

The `signalcontrollerwebui` component contains the web interface for the signal controller, which runs on a separate
Raspberry Pi device configured as a web server and reverse proxy for the `signalcontrollermain` component.

#### Hardware Requirements

* [\(x1\) Raspberry Pi 4 \(or newer\)](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)
    * [\(x1\) Raspberry Pi 4 Power Supply \(5.1V 3A\)](https://www.raspberrypi.com/products/type-c-power-supply/)
    * [\(x1\) MicroSD Card \(32GB or greater\)](https://a.co/d/49KQiNb)
    * [\(x1\) STP \(Shielded\) Ethernet Cable \(to connect PLC component\)](https://www.amazon.com/Startech-Shielded-Gigabit-Network-patch/dp/B019FPJMZE)

#### Software Requirements

The Raspberry Pi must be running the latest version of Raspbian OS and connected to a Wi-Fi network.

The following web server package must be installed:

* apache2 (`sudo apt install apache2 -y`)

and the following Apache2 modules must be enabled:

* mod_proxy (`sudo a2enmod proxy`)
* mod_proxy_http (`sudo a2enmod proxy_http`)
* proxy_balancer (`sudo a2enmod proxy_balancer`)
* lbmethod_byrequests (`sudo a2enmod lbmethod_byrequests`)

_Note: It is required to restart the Apache2 service after enabling the above modules. This can be done by running the
following command: `sudo systemctl restart apache2`_

#### Configuration

##### Networking

A static IP address is required for the Raspberry Pi to communicate with the PLC hosting the `signalcontrollermain`
component.

The PLC is configured by default to communicate with the Raspberry Pi at the IP address `10.0.0.2`, thus the Raspberry
Pi must be statically configured to use the same IP address `10.0.0.2`.

To configure the Raspberry Pi to use a static IP address, the `/etc/dhcpcd.conf` file must be modified to contain the
following content:

```bash
interface eth0
static ip_address=10.0.0.2/24
```

_Note: It is not recommended to set a default gateway or DNS server in the Raspberry Pi static network configuration, as
doing
so will prevent the Raspberry Pi from using its Wi-Fi connection to communicate with the internet/upstream network._

A resulting `/etc/dhcpcd.conf` file should look similar to the following:

```bash
# A sample configuration for dhcpcd.
# See dhcpcd.conf(5) for details.

# Allow users of this group to interact with dhcpcd via the control socket.
#controlgroup wheel

# Inform the DHCP server of our hostname for DDNS.
hostname

# Use the hardware address of the interface for the Client ID.
clientid
# or
# Use the same DUID + IAID as set in DHCPv6 for DHCPv4 ClientID as per RFC4361.
# Some non-RFC compliant DHCP servers do not reply with this set.
# In this case, comment out duid and enable clientid above.
#duid

# Persist interface configuration when dhcpcd exits.
persistent

# Rapid commit support.
# Safe to enable by default because it requires the equivalent option set
# on the server to actually work.
option rapid_commit

# A list of options to request from the DHCP server.
option domain_name_servers, domain_name, domain_search, host_name
option classless_static_routes
# Respect the network MTU. This is applied to DHCP routes.
option interface_mtu

# Most distributions have NTP support.
#option ntp_servers

# A ServerID is required by RFC2131.
require dhcp_server_identifier

# Generate SLAAC address using the Hardware Address of the interface
#slaac hwaddr
# OR generate Stable Private IPv6 Addresses based from the DUID
slaac private

# Example static IP configuration:
interface eth0
static ip_address=10.0.0.2/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
#static routers=10.0.0.1
#static domain_name_servers=192.168.0.1 8.8.8.8 fd51:42f8:caae:d92e::1

# It is possible to fall back to a static IP if DHCP fails:
# define static profile
#profile static_eth0
#static ip_address=192.168.1.23/24
#static routers=192.168.1.1
#static domain_name_servers=192.168.1.1

# fallback to static profile on eth0
#interface eth0
#fallback static_eth0
```

##### Web Server

The following Apache2 configuration files must be created with the specified content:

1. `/etc/apache2/sites-available/000-default.conf`
      ```bash
      <VirtualHost *:80>
      # The ServerName directive sets the request scheme, hostname and port that
      # the server uses to identify itself. This is used when creating
      # redirection URLs. In the context of virtual hosts, the ServerName
      # specifies what hostname must appear in the request's Host: header to
      # match this virtual host. For the default virtual host (this file) this
      # value is not decisive as it is used as a last resort host regardless.
      # However, you must set it for any further virtual host explicitly.
      #ServerName www.example.com

      ServerAdmin webmaster@localhost
      DocumentRoot /var/www/html
      Header add Access-Control-Allow-Origin "*"

      # Available loglevels: trace8, ..., trace1, debug, info, notice, warn,
      # error, crit, alert, emerg.
      # It is also possible to configure the loglevel for particular
      # modules, e.g.
      #LogLevel info ssl:warn

      ErrorLog ${APACHE_LOG_DIR}/error.log
      CustomLog ${APACHE_LOG_DIR}/access.log combined

      # For most configuration files from conf-available/, which are
      # enabled or disabled at a global level, it is possible to
      # include a line for only one particular virtual host. For example the
      # following line enables the CGI configuration for this host only
      # after it has been globally disabled with "a2disconf".
      #Include conf-available/serve-cgi-bin.conf
      </VirtualHost>
      ```
2. `/etc/apache2/sites-enabled/001-proxy.conf`
      ```bash
      <VirtualHost *:81>
        ProxyPreserveHost on
        ProxyPass / http://10.0.0.1:80/
        ProxyPassReverse / http://10.0.0.1:80/
       </VirtualHost>
       # vim: syntax=apache ts=4 sw=4 sts=4 sr noet
      ```

After creating the above files, the Apache2 service must be restarted by running: `sudo systemctl restart apache2`.

Once the Apache2 service has been restarted, the created configuration files must be enabled by running the following
commands:

1. `sudo a2ensite 000-default.conf`
2. `sudo a2ensite 001-proxy.conf`

Lastly, the Apache2 port configuration must be modified to allow the web server to listen on both port 80 and port 81.
To do this, add a new line `Listen 81` below the existing `Listen 80` entry in the `/etc/apache2/ports.conf` file. The
resulting file should look like the following:

```bash
# If you just change the port or add more ports here, you will likely also
# have to change the VirtualHost statement in
# /etc/apache2/sites-enabled/000-default.conf

Listen 80
Listen 81

<IfModule ssl_module>
        Listen 443
</IfModule>

<IfModule mod_gnutls.c>
        Listen 443
</IfModule>

# vim: syntax=apache ts=4 sw=4 sts=4 sr noet
```

After enabling the above configuration files and modifying the port configuration, the Apache2 service must be restarted
again by running: `sudo systemctl restart apache2`.
