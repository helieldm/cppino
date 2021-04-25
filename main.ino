class Timer
{
    unsigned long startTime;
    bool paused;
    unsigned long pauseTime;

public:
    Timer() : paused(false), pauseTime(0)
    {
        startTime = millis();
    }

    float getSeconds()
    {
        if (paused)
        {
            return (pauseTime - startTime) / 1000.0f;
        }
        unsigned long currentTime = millis();
        return (currentTime - startTime) / 1000.0f;
    }

    void pause()
    {
        if (paused)
        {
            return;
        }
        pauseTime = millis();
        paused = true;
    }

    void unpause()
    {
        if (!paused)
        {
            return;
        }
        unsigned long currentTime = millis();
        startTime += (currentTime - pauseTime);
        pauseTime = 0;
        paused = false;
    }

    void reset()
    {
        paused = false;
        startTime = millis();
        pauseTime = 0;
    }
};

Timer t;
bool on = false;

const char *lettresMorses[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

class MorseConverter
{

protected:
    MorseConverter() {}

    static MorseConverter *morseconverter_;

public:
    String *MorseReturn;

    MorseConverter(MorseConverter &other) = delete;

    void operator=(const MorseConverter &other) = delete;

    static MorseConverter *GetInstance();

    String readSerial();

    String *stringToMorse(String Input)
    {
        MorseReturn = {};
        int i = 0;

        while (Input[i] != '\0')
        {
            Input[i] = toUpperCase(Input[i]);
            if (Input[i] >= 'A' && Input[i] <= 'Z')
            {
                //Serial.print("\nInput I: ");
                //Serial.print(Input[i]);

                MorseReturn[i] = lettresMorses[Input[i] - 65];
                //Serial.print("\n\nTest:");
                String test = lettresMorses[Input[i] - 65];
                //Serial.print(test);
                //Serial.print("\n\n");
            }
            if (Input[i] == ' ')
            {
                MorseReturn[i] = " ";
            }
            i++;
        }
        return MorseReturn;
    }
};

String MorseConverter::readSerial()
{
    if (Serial.available() > 0)
    {
        return Serial.readString();
    }
    return "";
}

MorseConverter *MorseConverter::morseconverter_ = nullptr;
// Doit être définie hors de la classe
MorseConverter *MorseConverter::GetInstance()
{
    if (morseconverter_ == nullptr)
    {
        morseconverter_ = new MorseConverter();
    }
    return morseconverter_;
}

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    MorseConverter *mc = MorseConverter::GetInstance();
    int s = Serial.available();
    if (s > 0)
    {
        Serial.print(s);
    }
    if (Serial.available() > 0)
    {

        String read = mc->readSerial();
        Serial.print("\nRead:");
        Serial.print(read);
        Serial.print("\nWrite:");
        String *morse = mc->stringToMorse(read);
        int i = 0;
        while (i < 100)
        {
            //Serial.print(morse[i]);
            i++;
        }
    }
}
