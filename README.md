# Ledis
- WIP -
<p align="center">
  <img src="./docs/logo.png" height=300/>
</p>

Ledis or *Le*vent's *DI*ctionary *S*erver is a minor re-creation of Redis, which works as a in-memory caching server that created out of boredom. Ledis utilize the foundational functions of caching in memory. I just created this piece of software to have depper understanding on redis and experimenting on user-level networking with data structures used in cahing such as hash tables and AVL Trees.

I hate to say this word but I created Ledis to be _scaleable_ as much as possible. That means you can take the Ledis even change the protocol type and integrate to your project. Even tho it's not suitable for production i think it's a nice tool for minor projects and experimenting on behaviour of caching.

## Documents
- Ledis serving on Amazon AWS Ec2 Machine
  - Ledis performs on ec2 accepting requests
  - Identifying clients by their ip4 addresses
  - Parsing the request and send a response
  - ![Server](./docs/ledis_server.jpg)

- A client reachs Ledis on EC2
  - Client receives and sends request to Ledis
  - Getting a response from Ledis
  ![Client](./docs/ledis_client.jpg)


## License
Ledis is under [MIT](./LICENSE) license.
