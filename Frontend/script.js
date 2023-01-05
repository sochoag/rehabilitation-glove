const options = {
  // Authentication
  username: "glove-webapp",
  password: "10101011",

  connectTimeout: 4000,
  clientId: "browser_client_" + Math.random(),
  keepalive: 60,
  clean: true,
};

// Connection
const WebSocket_URL = "ws://sochoag.ga:8083/mqtt";
const client = mqtt.connect(WebSocket_URL, options);

client.on("connect", () => {
  console.log("Connect success");
  console.log("Yes!!!");

  client.subscribe("glove/fingers/sens", function (err) {
    if (!err) {
      console.log("SUBSCRIBE - SUCCESS");
    } else {
      console.log("SUBSCRIBE - ERROR");
    }
  });
});

client.on("reconnect", (error) => {
  console.log("reconnecting:", error);
});

client.on("error", (error) => {
  console.log("Connect Error:", error);
});

client.on("message", function (topic, message) {
  console.log(
    "The topic is " + topic + " and the message is " + message.toString()
  );

  //string to object
  const received = JSON.parse(message.toString());
  console.log(received);
  for (let llave of Object.keys(received)) {
    dedo(llave, received[llave]);
  }
});

function dedo(dedo, val) {
  let pValor = document.getElementById(dedo + "-value");
  let pIntensity = document.getElementById(dedo + "-intensity");
  let color = "";

  if (val < 25) {
    color = getComputedStyle(document.documentElement).getPropertyValue(
      "--low"
    );
    pIntensity.innerHTML = "Low";
  } else if (val < 50) {
    color = getComputedStyle(document.documentElement).getPropertyValue(
      "--medium"
    );
    pIntensity.innerHTML = "Medium";
  } else {
    color = getComputedStyle(document.documentElement).getPropertyValue(
      "--primary"
    );
    pIntensity.innerHTML = "High";
  }

  if (val == 100) {
    color = getComputedStyle(document.documentElement).getPropertyValue(
      "--done"
    );
    pIntensity.innerHTML = "Nice 😎";
  }

  if (val == 0) {
    color = getComputedStyle(document.documentElement).getPropertyValue(
      "--gray"
    );
    pIntensity.innerHTML = "Not detected";
  }

  pValor.innerHTML = val;
  pIntensity.style.color = color;
}
