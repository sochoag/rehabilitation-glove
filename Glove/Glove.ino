#include <U8g2lib.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Definimos el objeto para la pantalla OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

// Configuramos el cliente NTP para obtener la hora desde un servidor NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Definimos una constante con la cantidad de segundos en 5 horas
const int GMT_OFFSET = 18000;

void setup()
{
  // Inicializamos la conexión con la pantalla OLED
  u8g2.begin();

  // Inicializamos la conexión WiFi
  WiFi.begin("sochoagu", "sochoagu");

  // Esperamos a que se establezca la conexión WiFi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  // Inicializamos el cliente NTP
  timeClient.begin();
}

void loop()
{
  // Obtenemos la hora actual desde el servidor NTP
  timeClient.update();

  // Obtenemos la hora actual en formato Unix
  time_t hora_unix = timeClient.getEpochTime();

  // Ajustamos la hora para el huso horario de Ecuador
  hora_unix -= GMT_OFFSET;

  // Convertimos la hora ajustada a una estructura de tiempo
  struct tm *tm_struct = localtime(&hora_unix);

  // Convertimos la estructura de tiempo a una cadena de caracteres
  char hora_actual[9];
  sprintf(hora_actual, "%02d:%02d", tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);

  // Borramos la pantalla
  u8g2.clearBuffer();

  // Configuramos la fuente y el tamaño
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  // Wifi Indicator
  u8g2.drawGlyph(0, 11, 248);  // Wifi Icon
  u8g2.drawGlyph(16, 11, 115); // Check Icon

  // MQTT Indicator
  u8g2.drawGlyph(50, 11, 124); // Cloud Icon
  u8g2.drawGlyph(66, 11, 280); // Cross Icon

  u8g2.setFont(u8g2_font_t0_11_mf);
  u8g2.drawStr(9, 11, ":");
  u8g2.drawStr(59, 11, ":");

  // Escribimos la hora actual en la pantalla
  u8g2.drawStr(98, 11, hora_actual);
  u8g2.drawLine(0, 15, 128, 15);
  // u8g2.drawRBox(0, 0, 128, 15, 1);
  // Mostramos el contenido en la pantalla
  u8g2.sendBuffer();

  // Esperamos 1 segundo antes de actualizar la hora
  delay(1000);
}
