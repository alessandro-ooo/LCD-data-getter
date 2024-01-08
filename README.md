<br />
<div align="center">
  <h3 align="center">LCD-data-getter software</h3>

  <p align="center">
    Simple software to comunicate with your arduino board, send time, date and weather forecast.
    This repository only works with the LCD-clock project, <a href="https://github.com/alessandro-ooo/lcd1602-clock">you can find it here.</a>
    <br />
    <br />
    <br />
  </p>
</div>

## About The Project

<a href="https://youtube.com/shorts/mDV9INZrdto?feature=share">View Demo</a>

There are a lot of modern digital clocks available on the internet or in physical store, even good-looking ones. Though I've decided to create this software to comunicate with my arduino board and learn-by-doing how everything works with embedd softwares.
This software is by no means complete AND/OR indicated for professional use, it has to be considered as amateur project, hobbist software.

## How does everything work?

Basically, when the board is connected through USB to the computer, it "awaits" for data. It means that the arduino board sends (through serial communication) ```<weather>``` string to the software, the software "reads" and gets the weather data through ```LAT``` and ```LOG``` of your location, which it would be hard coded in the software.
The weather forecast is gathered through an API call to <a href="https://openweathermap.org/">https://openweathermap.org/</a> every ten minutes using the <a href="https://curl.se/">CURL library</a>. Once the weather data is stored in Arduino, the board will keep communicating to the software ```<time>``` string every second and will receive time and date to display on the LCD. It'll be possible to display the weather pressing a button.

## Docs

# class Reader
```cpp
string request(string request)
```
Returns a string.
Example:
```cpp
string response = read.request("<time>");
cout << response << endl;
// Output: 08/01/2024 12:00:00
```
# class Writer
```cpp
bool write(SimpleSerial* serial, string message)
```
returns a boolean.
Example:
```cpp
bool write = write.write(&Serial, "08/01/2024 12:00:00");
if(write == false {
  cout << "Impossible to write to the board" << endl;
}
else {
  cout << "Message sent" << endl;
}
```

# class Time
```cpp
string getTime()
```
returns ```day/month/year hour:minutes:seconds```
Example:
```cpp
void printSysTimeAndDate() {
  Time time;
  return time.getTime()
}

// Output: 08/01/2024 12:00:00
```

# class Weather
```cpp
string getWeather()
```
returns temperatures in celsius and current weather in Italian.
Example:
```cpp
string response = read.request("<weather>");
cout << response << endl;
// Output: 10C Soleggiato
```

```cpp
int KtoC(double kelvin)
```
Converts Kelvin to Celsius. It's needed because <a href="https://openweathermap.org/">https://openweathermap.org/</a> returns temperatures in Kelvin.
Returns: Celsius.
```cpp
const int C = KtoC(303.15)
cout << C << endl;
//Output: 30
// Absolute zero: 273,15. 303 K - 273,15 = 30 °C```

```cpp
string translate(string condition)
```
returns the translated weather conditions.
example:
```cpp
const translateRain = translate("Rain);
cout << translateRain << endl;
//Output: pioggia
```
