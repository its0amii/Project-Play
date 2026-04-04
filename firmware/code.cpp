#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adfruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <WiFi.h>
#include <spotify.h>

#define TFT_CS 1
#define TFT_RST 2
#define TFT_DC 3
#define TFT_SCLK 4
#define TFT_MOSI 5
#define BTN_BACK    8
#define BTN_PP      7
#define BTN_FWD     6

char* SSID = "our_wifi_ssid";
char* PASSWORD = "our_wifi_password";
const char* CLIENT_ID = "spotify_client_id THAT YOU GET FROM SPOTIFY DASHBOARD";
const char* CLIENT_SECRET = "spotify_client_secret THAT YOU GET FROM SPOTIFY DASHBOARD";

String lastArtist;
String lastTrackname;

spotify sp(CLIENT_ID, CLIENT_SECRET);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
 
void setup(){
    Serial.begin(115200);
    tft.initR(INITR_BLACKTAB);?? the type of screan you are yuseing for this projrct
    tft.setRotation(1);// 1 make landscapr mode and 0 make portrait mode
    Serial.println("TFT Initialized");
    tft.fillScreen(ST7735_BLACK);// set bg color into black

    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to WiFi!!!");
    while (WiFi.status()!= WL_CONNECTED)

    {
        delay(1000);
        Serial.print("!");
    }
    Serial.printf("\n Connected to WiFi!\n");
    sp.begin();
    while(!sp.is_auth()){
        sp.handle_client();
    }
    Serial.println("Authenticated with Spotify!!!");


// In setup():
pinMode(BTN_BACK, INPUT_PULLUP);
pinMode(BTN_PP,   INPUT_PULLUP);
pinMode(BTN_FWD,  INPUT_PULLUP);
}

void loop()
{
    String currentArtist = sp.current_artist_names();
    String currentTrackname = sp.current_track_name();

    if (lastArtist != currentArtist && currentArtist != "Something went wrong" && !currentArtist.isEmpty()) {
        tft.fillScreen(ST77XX_BLACK);
        lastArtist = currentArtist;
        Serial.println("Artist: " + lastArtist);
        tft.setCursor(10,10);
        tft.write(lastArtist.c_str());
    }

    if (lastTrackname != currentTrackname && currentTrackname != "Something went wrong" && currentTrackname != "null") {
        lastTrackname = currentTrackname;
        Serial.println("Track: " + lastTrackname);
        tft.setCursor(10,40);
        tft.write(lastTrackname.c_str());
    }
    delay(2000);
}
 