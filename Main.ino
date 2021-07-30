#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#include <LiquidCrystal.h>

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/*
 * Display fixe text .
 */
void setup( )
{
  lcd.begin(16, 2);
  lcd.print( "T = " );
  lcd.setCursor(10, 0);
  lcd.print( "deg. C" );
  lcd.setCursor(0, 1);
  lcd.print( "H = " );
  lcd.setCursor(10, 1);
  lcd.print( "%" );
  pinMode(5,OUTPUT); //voltage output
}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure temperature and humdity once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

/*
 * Main program loop.
 */
void loop( )
{
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
   /*
    * Display changing text.
    */
    lcd.setCursor(4, 0);
    lcd.print( temperature );
    lcd.setCursor(4, 1);
    lcd.print( humidity );
    
    if(temperature >= 30) {
          analogWrite(5,255); //Turn on USB power output
        } 
        else if (temperature < 25){ 
          analogWrite(5,0); //Turn off USB power output
          }
        
  }
}
