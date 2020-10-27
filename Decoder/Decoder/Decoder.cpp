// Decoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    system("pause>0");
}


void decodeFile(const char* fileName)
{
    FILE* inFile;
    errno_t err = fopen_s(&inFile, fileName, "rb");
    int8_t val_s8;
    uint8_t val_u8;
    uint32_t val_u32;
    int16_t val_s16;
    int32_t ch_idx = 0;
    int32_t fileSize;

    if (err != 0)
    {
        printf("%s: Cannot open file\n", fileName);
        return;
    }

    fseek(inFile, 0L, SEEK_END);
    fileSize = ftell(inFile);
    rewind(inFile);

    fread(&val_s8, sizeof(val_s8), 1, inFile);
    if (val_s8 != 1)
    {
        printf("%s: Uknown encoding version\n", fileName);
        return;
    }

    int bytesRemaining = fileSize - ftell(inFile);

    while (bytesRemaining > 1)
    {
        fread(&val_u32, sizeof(val_u32), 1, inFile);

        int32_t timeOfDay = (val_u32 >> 0) & 0x7FF;
        int32_t interval = (val_u32 >> 11) & 0x7FF;
        int32_t measurementCnt = (val_u32 >> 22) & 0x1F;
        int32_t deltaType = (val_u32 >> 27) & 0x3;
        int32_t precision = (val_u32 >> 29) & 0x7;

       /* MeasurementCh_t* pCh = &measurementSet.channel[ch_idx];

        int32_t mIdx = pCh->measurementCnt + measurementCnt - 1;*/

        int32_t mIdx = measurementCnt - 1;

        int16_t nextVal;
        int32_t nextTime;

        float scalingFactor = 1;
        for (int i = 0; i < precision; i++)
        {
            scalingFactor *= 10;
        }

        for (int i = 0; i < measurementCnt; i++)
        {
            if (i == 0)
            {
                fread(&val_s16, sizeof(val_s16), 1, inFile);
                nextVal = val_s16;
                nextTime = timeOfDay * 60;
            }
            else
            {
                switch (deltaType)
                {
                case 0:
                    nextVal = nextVal + 0;
                    break;
                case 1:
                    fread(&val_s8, sizeof(val_s8), 1, inFile);
                    nextVal = nextVal + val_s8;
                    break;
                case 2:
                    fread(&val_s16, sizeof(val_s16), 1, inFile);
                    nextVal = val_s16;
                    break;
                default:
                case 3:
                    printf("%s: Unknown encoding delta\n", fileName);
                    return;
                }

            }

           /* pCh->measurement[mIdx].timeStamp = nextTime;
            pCh->measurement[mIdx].value = (float)nextVal / scalingFactor;*/

            mIdx--;
            nextTime -= interval * 60;
        }

        /*pCh->measurementCnt += measurementCnt;*/
        ch_idx++;
        bytesRemaining = fileSize - ftell(inFile);
    }

    fread(&val_u8, sizeof(val_u8), 1, inFile);
    uint8_t batteryCV = val_u8;

    /*if (ch_idx > measurementSet.channelCnt)
    {
        measurementSet.channelCnt = ch_idx;
    }*/
    fclose(inFile);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
