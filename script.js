let btnConectar = document.getElementById("btnConectar");
let btnDesconectar = document.getElementById("btnDesconectar");
let sliderFreq = document.getElementById("frecSlider");
let btnFreq = document.getElementById("btnFreq");

btnConectar.addEventListener("click", connectMQTT);
btnDesconectar.addEventListener("click", disconnectMQTT);
sliderFreq.addEventListener("input", updateFreq);
btnFreq.addEventListener("click", freqPublish);

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

let client;
// Connection
const WebSocket_URL = "wss://sochoag.com:8084/mqtt";
let freqVal = 3000;

function connectMQTT() {
  let username = document.getElementById("username");
  let password = document.getElementById("password");
  options.username = username.value;
  options.password = password.value;
  client = mqtt.connect(WebSocket_URL, options);
  client.on("connect", () => {
    client.subscribe("glove/fingers/sens", function (err) {
      if (!err) {
        alert("Conexión MQTT exitosa 😎");
        username.disabled = true;
        password.disabled = true;
        btnConectar.disabled = true;

        btnDesconectar.disabled = false;
        btnFreq.disabled = false;
        sliderFreq.disabled = false;
      }
    });
  });

  client.on("error", (error) => {
    alert("Error al conectar MQTT 😥");
    password.value = "";
    client.end();
    return;
  });

  client.on("reconnect", (error) => {
    console.log("reconnecting:", error);
  });

  client.on("message", function (topic, message) {
    if (topic == "glove/fingers/sens") {
      const received = JSON.parse(message.toString());
      for (let llave of Object.keys(received)) {
        dedo(llave, received[llave]);
      }
    } else {
      console.log("No se reconoce acciones para el topico:" + topic);
    }
  });
}

function disconnectMQTT() {
  client.end();
  username.disabled = false;
  password.disabled = false;
  btnConectar.disabled = false;

  btnDesconectar.disabled = true;
  btnFreq.disabled = true;
  sliderFreq.disabled = true;
}

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
    pIntensity.innerHTML = "No detected";
  }

  pValor.innerHTML = val;
  pIntensity.style.color = color;
}

function updateFreq() {
  console.log(sliderFreq.value);
  document.getElementById("freqVal").innerText = sliderFreq.value;
  freqVal = sliderFreq.value;
}

function freqPublish() {
  console.log("Changing Frequency to: " + freqVal);
  client.publish("glove/fingers/acts", freqVal, { retain: true });
  alert("Frecuencia cambiada correctamente ✔");
}
