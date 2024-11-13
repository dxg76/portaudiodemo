#include <stdlib.h>
#include <iostream>
#include <portaudio.h>

static void checkErr(PaError err){
    if(err != paNoError){

    printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    Pa_Terminate();
    exit(EXIT_FAILURE);

    }
}

int main(){
PaError err;
err = Pa_Initialize();
checkErr(err);

int numDevices = Pa_GetDeviceCount();
printf("Number of Devices: %s\n", Pa_GetErrorText(numDevices));
printf("Number of Devices: %d\n", numDevices);

if (numDevices < 0) {
    std::cerr << "ERROR: Pa_CountDevices returned " << numDevices << std::endl;
    std::cerr << "Error message: " << Pa_GetErrorText(numDevices) << std::endl;
    Pa_Terminate();
    return EXIT_FAILURE;
}

const PaDeviceInfo* deviceInfo;
for (int i = 0; i < numDevices; i++) {
    deviceInfo = Pa_GetDeviceInfo(i);
    std::cout << "Device #" << i << ": " << deviceInfo->name << std::endl;
    std::cout << "  Max Input Channels: " << deviceInfo->maxInputChannels << std::endl;
    std::cout << "  Max Output Channels: " << deviceInfo->maxOutputChannels << std::endl;
    std::cout << "  Default Sample Rate: " << deviceInfo->defaultSampleRate << std::endl;
}

PaHostApiIndex defaultHostApi = Pa_GetDefaultHostApi();
const PaHostApiInfo* hostApiInfo = Pa_GetHostApiInfo(defaultHostApi);
std::cout << "Default Host API: " << hostApiInfo->name << std::endl;

err = Pa_Terminate();
checkErr(err);

return EXIT_SUCCESS;
}