# esp32-bme280-twowire-i2c
These sensors had pads to change the i2c addresses to different ones. But what if you cannot change an i2c address?
You use the two wire protocol and utilize both sets of i2c interfaces of your esp32!

![alt text](https://raw.githubusercontent.com/ran-sama/esp8266-bme280-udp-tcp-http-server/master/twowire_same_address.jpg)

For convenience you can push send the sensor readings via UDP to a listener, or pull them off a HTTP server with TCP.

## License
Licensed under the WTFPL license.
