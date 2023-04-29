#include <U8g2lib.h>

// Definimos el objeto para la pantalla OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void oledSetup()
{
  // Inicializamos la conexión con la pantalla OLED
  u8g2.begin();
}

void loopOled()
{
  // Borramos la pantalla
  u8g2.clearBuffer();

  // Configuramos la fuente y el tamaño
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  // Wifi Indicator
  u8g2.drawGlyph(0, 11, 248);  // Wifi Icon
  u8g2.drawGlyph(16, 11, 115); // Check Icon
  // MQTT Indicator
  u8g2.drawGlyph(50, 11, 124); // Cloud Icon
  u8g2.drawGlyph(66, 11, 115); // Cross Icon

  u8g2.setFont(u8g2_font_mozart_nbp_tf);
  u8g2.drawStr(9, 11, ":");
  u8g2.drawStr(59, 11, ":");

  // Escribimos la hora actual en la pantalla
  u8g2.drawStr(98, 11, hora_actual);
  u8g2.drawLine(0, 15, 128, 15);

  u8g2.drawStr(0, 24, "Menique:");
  u8g2.drawStr(0, 34, "Anular:");
  u8g2.drawStr(0, 44, "Indice:");
  u8g2.drawStr(0, 54, "Medio:");
  u8g2.drawStr(0, 64, "Pulgar:");

  u8g2.drawStr(50, 24, String(flexRead[0]).c_str());
  u8g2.drawStr(50, 34, String(flexRead[1]).c_str());
  u8g2.drawStr(50, 44, String(flexRead[2]).c_str());
  u8g2.drawStr(50, 54, String(flexRead[3]).c_str());
  u8g2.drawStr(50, 64, String(flexRead[4]).c_str());

  u8g2.drawStr(72, 24, "-");
  u8g2.drawStr(72, 34, "-");
  u8g2.drawStr(72, 44, "-");
  u8g2.drawStr(72, 54, "-");

  u8g2.drawStr(83, 24, phalangesRead[0].c_str());
  u8g2.drawStr(83, 34, phalangesRead[1].c_str());
  u8g2.drawStr(83, 44, phalangesRead[2].c_str());
  u8g2.drawStr(83, 54, phalangesRead[3].c_str());
  // Mostramos el contenido en la pantalla
  u8g2.sendBuffer();
}

void oledWifi()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_mozart_nbp_tf);
  u8g2.drawStr(0, 11, "Conexion wifi"); // Wifi Icon
  u8g2.drawLine(0, 15, 128, 15);
  u8g2.setCursor(0, 24);
  u8g2.printf("SSID:%s", ssid);
  u8g2.setCursor(0, 34);
  u8g2.printf("PASS:%s", password);
  u8g2.sendBuffer();
}

void oledMQTT()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_mozart_nbp_tf);
  u8g2.drawStr(0, 11, "Conexion MQTT"); // Wifi Icon
  u8g2.drawLine(0, 15, 128, 15);
  u8g2.setCursor(0, 24);
  u8g2.printf("Server:%s", mqtt_server);
  u8g2.setCursor(0, 34);
  u8g2.printf("Username:%s", mqtt_username);
  u8g2.setCursor(0, 44);
  u8g2.printf("Password:%s", mqtt_password);
  u8g2.sendBuffer();
}