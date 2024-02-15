#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include "Adafruit_SSD1306.h"
#include "esp_camera.h"

#include "cam_pins.h"

#include "display_pins.h"

Adafruit_SSD1306 display(0x3c, OLED_SDA, OLED_SCL);

void setup() {
	Serial.begin(115200);

	Serial.println("Inicializujem...");
 	camera_config_t cfg;
 	cfg.ledc_channel = LEDC_CHANNEL_0;
 	cfg.ledc_timer = LEDC_TIMER_0;
 	cfg.pin_d0 = Y2_GPIO_NUM;
	cfg.pin_d1 = Y3_GPIO_NUM;
	cfg.pin_d2 = Y4_GPIO_NUM;
	cfg.pin_d3 = Y5_GPIO_NUM;
	cfg.pin_d4 = Y6_GPIO_NUM;
	cfg.pin_d5 = Y7_GPIO_NUM;
	cfg.pin_d6 = Y8_GPIO_NUM;
	cfg.pin_d7 = Y9_GPIO_NUM;
	cfg.pin_xclk = XCLK_GPIO_NUM;
	cfg.pin_pclk = PCLK_GPIO_NUM;
	cfg.pin_vsync = VSYNC_GPIO_NUM;
	cfg.pin_href = HREF_GPIO_NUM;
	cfg.pin_sscb_sda = SIOD_GPIO_NUM;
	cfg.pin_sscb_scl = SIOC_GPIO_NUM;
	cfg.pin_pwdn = PWDN_GPIO_NUM;
	cfg.pin_reset = RESET_GPIO_NUM;
 	cfg.xclk_freq_hz = 20000000;
 	cfg.pixel_format = PIXFORMAT_GRAYSCALE; 
 	cfg.frame_size = FRAMESIZE_VGA; 
 	cfg.jpeg_quality = 12; 
 	cfg.fb_count = 1; 

 	esp_err_t err = esp_camera_init(&cfg);
 	if (err != ESP_OK) {
 		Serial.printf("Chyba pri inicializácií kamery: 0x%x\n", err);
 		return;
 	}

	if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_WIDTH, SCREEN_HEIGHT)) {
		Serial.println("Chyba pri inicializácií displeja");
		return;
	}

	display.clearDisplay();
	Serial.println("OK");
}

void loop() {
	camera_fb_t *fb = esp_camera_fb_get();
	if (!fb) {
		Serial.println("Chyba pri snímaní obrazu z kamery");
		return;
	}

 
	display.clearDisplay();
	display.drawBitmap(0, 0, fb->buf, fb->width, fb->height, WHITE);
	display.display();

	esp_camera_fb_return(fb);

	delay(40); // 1000 ms / 25 FPS = 40 ms
}