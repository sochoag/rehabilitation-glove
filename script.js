let btnConectar = document.getElementById("btnConectar");
let btnDesconectar = document.getElementById("btnDesconectar");
let sliderFreq = document.getElementById("frecSlider");
let btnFreq = document.getElementById("btnFreq");

btnConectar.addEventListener("click", connectMQTT);
btnDesconectar.addEventListener("click", disconnectMQTT);
sliderFreq.addEventListener("input", updateFreq);
btnFreq.addEventListener("click", freqPublish);

let client;
// Connection

let freqVal = 3000;

function connectMQTT() {
  let username = document.getElementById("username");
  let password = document.getElementById("password");
  options.username = username.value;
  options.password = password.value;
  client = mqtt.connect(WebSocket_URL, options);
  client.on("connect", () => {
    topics.forEach((topic) => {
      client.subscribe(topic);
    });
    alert("Conexión MQTT exitosa 😎");
    username.disabled = true;
    password.disabled = true;
    btnConectar.disabled = true;

    btnDesconectar.disabled = false;
    btnFreq.disabled = false;
    sliderFreq.disabled = false;
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
    const received = JSON.parse(message.toString());
    if (topic == "glove/fingers/flex") {
      for (let llave of Object.keys(received)) {
        dedo(llave, received[llave]);
      }
    } else if (topic == "glove/fingers/touch") {
      for (let llave of Object.keys(received)) {
        touch(llave, received[llave]);
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
  pValor.innerHTML = val;
  changeClass(pValor, val);
}

function touch(dedo, val) {
  let pTouch = document.getElementById(dedo + "-touch");
  changeClass(pTouch, val);
  pTouch.innerHTML = val;
}

function changeClass(el, val) {
  if (val == 0 || val == "") {
    el.classList.add("gray");
    el.classList.remove("low");
    el.classList.remove("medium");
    el.classList.remove("high");
  } else if (val < 25 || val == "Proximal") {
    el.classList.remove("gray");
    el.classList.add("low");
    el.classList.remove("medium");
    el.classList.remove("high");
  } else if (val < 50 || val == "Medial") {
    el.classList.remove("gray");
    el.classList.remove("low");
    el.classList.add("medium");
    el.classList.remove("high");
  } else {
    el.classList.remove("gray");
    el.classList.remove("low");
    el.classList.remove("medium");
    el.classList.add("high");
  }
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
