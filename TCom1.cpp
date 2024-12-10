#include "TCom1.hpp"

TCom1::TCom1(const char *name, void *shared, int priority, baudrate_t baudRate, parity_t parity, dimData_t dimData, int32_t timeoutRxMs)
	: TCom(name, shared, priority, baudRate, parity, dimData, timeoutRxMs), screen(nullptr)
{
	screen = (TScreen *)shared;
	//screen->dispStr(1, 2, name);
	//screen->dispStr(1, 3, com);
}

TCom1::~TCom1()
{
}

void TCom1::rxCar(unsigned char car)
{
	enum State
	{
		WAITING_FOR_SLAVE_ADDRESS,
		WAITING_FOR_FUNCTION_CODE,
		WAITING_FOR_BYTE_COUNT,
		WAITING_FOR_DATA,
		WAITING_FOR_CRC
	};

	static State state = WAITING_FOR_SLAVE_ADDRESS;
	static unsigned char buffer[9];
	static int bufferIndex = 0;
	static int dataLength = 0;

	switch (state)
	{
	case WAITING_FOR_SLAVE_ADDRESS:
		if (car == 0x02)
		{
			state = WAITING_FOR_FUNCTION_CODE;
			buffer[bufferIndex++] = car; //0
		}
		else
		{
			partage->setWait(false);
			partage->setModbusValue(0000);
			//send error connexion
			bufferIndex = 0;
		}
		break;
	case WAITING_FOR_FUNCTION_CODE:
		if (car == 0x03)
		{
			state = WAITING_FOR_BYTE_COUNT;
			buffer[bufferIndex++] = car; //1
		}
		else
		{
			state = WAITING_FOR_SLAVE_ADDRESS;
			bufferIndex = 0;
			partage->setWait(false);
			partage->setModbusValue(0000);
			//send error connexion
		}
		break;
	case WAITING_FOR_BYTE_COUNT:
		dataLength = car;
		buffer[bufferIndex++] = car; //2
		state = WAITING_FOR_DATA;
		break;
	case WAITING_FOR_DATA:
		buffer[bufferIndex++] = car;
		if (bufferIndex == 3 + dataLength)
		{
			state = WAITING_FOR_CRC;
		}
		break;
	case WAITING_FOR_CRC:
		buffer[bufferIndex++] = car;
		if (bufferIndex == 3 + dataLength + 2)
		{
			unsigned int receivedCrc = (buffer[bufferIndex - 2] << 8) | buffer[bufferIndex - 1];
			unsigned int calculatedCrc = calculerCRC(buffer, bufferIndex - 2);
			if (receivedCrc == calculatedCrc)
			{
				
				float value;
				uint8_t *pVal = (uint8_t *)&value;
				pVal[0] = buffer[6];
				pVal[1] = buffer[5];
				pVal[2] = buffer[4];
				pVal[3] = buffer[3];
				screen->dispStr(1, 11, value);
				partage->setModbusValue(value);
				partage->setWait(false);
				bufferIndex = 0;
				dataLength = 0;
			}
			else
			{
				// Handle CRC error
				screen->dispStr(1, 11, "CRC error");
				partage->setWait(false);
				partage->setModbusValue(0000);
				bufferIndex = 0;
				//send error connexion
			}
			state = WAITING_FOR_SLAVE_ADDRESS;
			bufferIndex = 0;
		}
		break;
	}
}

void TCom1::rxTimeout(void)
{
	if (screen)
	{
		screen->dispStr(1, 4, "Receive timeout.");
	}
}

std::string TCom1::getComConfig(std::string nameFichierConfig)
{
	TConfiguration config(nameFichierConfig);
	return config.getParametreConfiguration();
}