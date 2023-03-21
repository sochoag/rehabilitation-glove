const WebSocket_URL = "wss://sochoag.com:8084/mqtt";

const options = {
  connectTimeout: 4000,
  clientId:
    "glove-webapp-" +
    Math.floor(Math.random() * 0xffff)
      .toString(16)
      .toUpperCase(),
  keepalive: 60,
  clean: true,
};

const topics = ["glove/fingers/flex", "glove/fingers/touch"];
