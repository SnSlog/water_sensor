-----------------------Подлкючение к MQTT-----------------------
https://techtutorialsx.com/2017/04/09/esp8266-connecting-to-mqtt-broker/ 

-----------------------Сертификат-----------------------
Для заливки файла в специальную область памяти необходимо использовать библиотеку FS.h и утилиту для ARDUINO IDE ESP8266 Sketch Data Upload
Рабочий вариант FS.h качать тут  https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.2.0/ESP8266FS-0.2.0.zip

Сертификат в формате .der помещается в подпапку /data/ скетча.

-----------------------Формат сертификата-----------------------
При попытке конвертирования сертификата из .crt в .der возникает ошибка "unable to load certificate...error:0906D06C: PEM routines..."
Вообще говоря, есть два вида кодировки: pem и der. При попытке работать с форматом в отличной от его собственной
кодировки, возникает эта ошибка. 
Для этого необходимо изменить кодировку файла на .pem. После чего вернуться в der.

openssl x509 -in cert,crt -inform der -out cert.pem -ourform pem
openaal x509 -in cert.pem -out cert.der -outform der

Источник: http://info.ssl.com/article.aspx?id=12149