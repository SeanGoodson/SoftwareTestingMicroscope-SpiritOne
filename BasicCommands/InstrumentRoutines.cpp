
#include "InstrumentRoutines.h"
#include "OphirLMMeasurement.h"
#include <iostream>
#include <iomanip>
#include <comdef.h>
OphirLMMeasurement OphirLM;
void PlugAndPlayCallback()
{
	std::wcout << L"Device has been removed from the USB. \n";
}
void DataReadyCallback(long hDevice, long channel)
{
	std::vector<double> values;
	std::vector<double> timestamps;
	std::vector<OphirLMMeasurement::Status> statuses;

	OphirLM.GetData(hDevice, channel, values, timestamps, statuses);
	for (size_t i = 0; i < values.size(); ++i)
		std::wcout << L"Timestamp: " << std::fixed << std::setprecision(3) << timestamps[i]
		<< L" Reading: " << std::scientific << values[i] << L" Status: " << OphirLM.StatusString(statuses[i]) << L"\n";
}

int InstrumentRoutines::ScanPowerMeter() {

	// a basic sample of using the CPlus_Demo	
	try
	{
		std::vector<std::wstring> serialNumbers, options;
		std::wstring info, headSN, headType, headName, version;
		std::wstring deviceName, romVersion, serialNumber;
		long hDevice = 0, channel = 0;

		// Scan for connected Devices
		OphirLM.ScanUSB(serialNumbers);
		std::wcout << serialNumbers.size() << L" Ophir USB devices found. \n";

		if (serialNumbers.size() > 0)
		{
			//open first device
			OphirLM.OpenUSBDevice(serialNumbers[0].c_str(), hDevice);
			std::wcout << L"Ophir device opened with handle " << hDevice << L".\n\n";

			//get device info
			OphirLM.GetDeviceInfo(hDevice, deviceName, romVersion, serialNumber);
			std::wcout << L"Device Name:   " << deviceName << L" \n";
			std::wcout << L"Rom Version:   " << romVersion << L" \n";
			std::wcout << L"Serial Number: " << serialNumber << L" \n\n";

			//get sensor info of first device
			OphirLM.GetSensorInfo(hDevice, channel, headSN, headType, headName);
			std::wcout << L"Head name:          " << headName << L" \n";
			std::wcout << L"Head type:          " << headType << L" \n";
			std::wcout << L"Head serial number: " << headSN << L" \n\n";

			//start measuring on first device
			OphirLM.RegisterPlugAndPlay(PlugAndPlayCallback);
			OphirLM.RegisterDataReady(DataReadyCallback);
			OphirLM.StartStream(hDevice, channel);

			//A message loop is necessary to receive events. 
			//An alternative is to call GetData in a loop (with a small delay in the loop) and not use events at all.
			MSG Msg;
			while (GetMessage(&Msg, NULL, 0, 0) > 0) {
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}

			OphirLM.StopAllStreams(); //stop measuring
			OphirLM.CloseAll(); //close device
		}
	}

	catch (const _com_error& e)
	{
		std::wcout << L"Error 0x" << std::hex << e.Error() << L" " << e.Description() << L"\n";
		// 0x00000000 (S_OK) : No Error
		// 0x80070057 (E_INVALIDARG) : Invalid Argument
		// 0x80040201 : Device Already Opened
		// 0x80040300 : Device Failed
		// 0x80040301 : Device Firmware is Incorrect
		// 0x80040302 : Sensor Failed
		// 0x80040303 : Sensor Firmware is Incorrect
		// 0x80040306 : This Sensor is Not Supported
		// 0x80040308 : The Device is no longer Available
		// 0x80040405 : Command Failed
		// 0x80040501 : A channel is in Stream Mode
	}
	return 0;


}