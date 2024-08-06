# udp-sender
## Simple tool for sending UDP packets

In the data field insert packet data captured by tcpdump -X, like the following:

```
0x0000:  4500 006e 970e 0000 7111 26ef 3e76 5010  E..n....q.&.>vP. 
0x0010:  b061 4c9a 6207 01bb 005a c872 73ad 3dc8  .aL.b....Z.rs.=.
0x0020:  175e df58 c3c3 806d eb86 6f08 3c62 ff95  .^.X...m..o.<b..
0x0030:  16ef e77e 2955 5c83 803c f941 d0ae bd96  ...~)U\..<.A....
0x0040:  6f03 4d65 9a5c 5907 2095 159e ce9d cf0d  o.Me.\Y.........
0x0050:  6718 db5f 92cf f154 4285 9934 a87c 0216  g.._...TB..4.|..
0x0060:  b41d 3ae8 19fd f8fb 6fa0 d352 230c       ..:.....o..R#.
```

Header will be replaced automatically 
