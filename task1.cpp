#include "task1.hpp"

TTask1::TTask1(const char *name, void *shared, int32_t policy, int32_t priority, int32_t cpu) : TThread(name, shared, policy, priority, cpu)
{
	std::string nameMqtt;

	screen = (TScreen *)shared;

	partage = TPartage::getInstance();

	com1 = new TCom1(TCom1::getComConfig("com.def").c_str(), screen, 10, TCom::b9600, TCom::pNONE, TCom::dS8, 10000);
	com1->start();

	nameMqtt = TMqtt::getMqttConfig();
	mqtt = new TMqtt(screen, "MqttPM", nameMqtt.c_str());

	screen->dispStr(1, 10, "Task MQTT (CPU :  ) :");
	screen->dispStr(30, 10, nameMqtt.c_str());
}

TTask1::~TTask1()
{
	if (mqtt)
		delete mqtt;
}

void TTask1::task(void)
{
	// variable locale
	unsigned char request[8];
	unsigned int crc = 0;
	float vanValue;
	float vbnValue;
	float vabValue;
	float iaValue;
	float ibValue;
	float kwValue;
	float fpValue;
	float kwhValue;
	float van;
	float vbn;
	float vab;
	float ia;
	float ib;
	float kw;
	float fp;
	float kwh;
	int index = 0;
	char vanStr[10];
	char vbnStr[10];
	char vabStr[10];
	char iaStr[10];
	char ibStr[10];
	char kwStr[10];
	char fpStr[10];
	char kwhStr[10];
	// synchronisation démarrage tâche
	signalStart();

	sleep(2);

	while (1)
	{
		switch (index)
		{
		case 0:
			// Modbus request format Van
			request[0] = 0x02; // Slave address
			request[1] = 0x03; // Function code (Read Holding Registers)
			request[2] = 0x03; // High byte of address (fixed as 0x03)
			request[3] = 0x14; // Low byte of address
			request[4] = 0x00; // Number of registers high byte
			request[5] = 0x02; // Number of registers low byte
			crc = calculerCRC(request, 6);
			request[6] = (crc >> 8); // CRC high byte
			request[7] = crc & 0xFF; // CRC low byte
			com1->sendTx(request, 8);
			partage->setWait(true);
			while (partage->getWait() == true)
			{
				screen->dispStr(1, 15, "WAIT   ");
				usleep(10000); // Sleep for 10ms to avoid busy waiting
			}
			screen->dispStr(1, 15, "NO WAIT");
			van = partage->getModbusValue();
			if (van != partage->getVan())
			{
				partage->setVan(van);
				vanValue = partage->getVan();
				snprintf(vanStr, sizeof(vanStr), "%.2f", vanValue);
				mqtt->publish(NULL, "RAM/powermeter/etats/Van", strlen(vanStr), vanStr);
			}
			screen->dispStr(1, 2, "Van : " + std::to_string(vanValue));
			break;

		case 1:
			// Modbus request format Vbn
			request[0] = 0x02; // Slave address
			request[1] = 0x03; // Function code (Read Holding Registers)
			request[2] = 0x03; // High byte of address (fixed as 0x03)
			request[3] = 0x16; // Low byte of address
			request[4] = 0x00; // Number of registers high byte
			request[5] = 0x02; // Number of registers low byte
			crc = calculerCRC(request, 6);
			request[6] = (crc >> 8); // CRC high byte
			request[7] = crc & 0xFF; // CRC low byte
			com1->sendTx(request, 8);
			partage->setWait(true);
			while (partage->getWait() == true)
			{
				screen->dispStr(1, 15, "WAIT   ");
				usleep(10000); // Sleep for 10ms to avoid busy waiting
			}
			screen->dispStr(1, 15, "NO WAIT");
			vbn = partage->getModbusValue();
			if (vbn != partage->getVbn())
			{
				partage->setVbn(vbn);
				vbnValue = partage->getVbn();
				sprintf(vbnStr, "%.2f", vbnValue);
				mqtt->publish(NULL, "RAM/powermeter/etats/Vbn", strlen(vbnStr), vbnStr);
			}
			screen->dispStr(1, 3, "Vbn : " + std::to_string(vbnValue));
			break;

		case 2:
			// Modbus request format Vab
			request[0] = 0x02; // Slave address
			request[1] = 0x03; // Function code (Read Holding Registers)
			request[2] = 0x03; // High byte of address (fixed as 0x03)
			request[3] = 0x1A; // Low byte of address
			request[4] = 0x00; // Number of registers high byte
			request[5] = 0x02; // Number of registers low byte
			crc = calculerCRC(request, 6);
			request[6] = (crc >> 8); // CRC high byte
			request[7] = crc & 0xFF; // CRC low byte
			com1->sendTx(request, 8);
			partage->setWait(true);
			while (partage->getWait() == true)
			{
				screen->dispStr(1, 15, "WAIT   ");
				usleep(10000); // Sleep for 10ms to avoid busy waiting
			}
			screen->dispStr(1, 15, "NO WAIT");
			vab = partage->getModbusValue();
			if (vab != partage->getVab())
			{
				partage->setVab(vab);
				vabValue = partage->getVab();
				sprintf(vabStr, "%.2f", vabValue);
				mqtt->publish(NULL, "RAM/powermeter/etats/Vab", strlen(vabStr), vabStr);
			}
			screen->dispStr(1, 4, "Vab : " + std::to_string(vabValue));
			break;

		case 3:
			// Modbus request format Ia
			request[0] = 0x02; // Slave address
			request[1] = 0x03; // Function code (Read Holding Registers)
			request[2] = 0x03; // High byte of address (fixed as 0x03)
			request[3] = 0x20; // Low byte of address
			request[4] = 0x00; // Number of registers high byte
			request[5] = 0x02; // Number of registers low byte
			crc = calculerCRC(request, 6);
			request[6] = (crc >> 8); // CRC high byte
			request[7] = crc & 0xFF; // CRC low byte
			com1->sendTx(request, 8);
			partage->setWait(true);
			while (partage->getWait() == true)
			{
				screen->dispStr(1, 15, "WAIT   ");
				usleep(10000); // Sleep for 10ms to avoid busy waiting
			}
			screen->dispStr(1, 15, "NO WAIT");
			ia = partage->getModbusValue();
			if (ia != partage->getIa())
			{
				partage->setIa(ia);
				iaValue = partage->getIa();
				sprintf(iaStr, "%.2f", iaValue);
				mqtt->publish(NULL, "RAM/powermeter/etats/Ia", strlen(iaStr), iaStr);
			}
			screen->dispStr(1, 5, "Ia : " + std::to_string(iaValue));
			break;

		case 4:
			// Modbus request format Ib
			request[0] = 0x02; // Slave address
			request[1] = 0x03; // Function code (Read Holding Registers)
			request[2] = 0x03; // High byte of address (fixed as 0x03)
			request[3] = 0x22; // Low byte of address
			request[4] = 0x00; // Number of registers high byte
			request[5] = 0x02; // Number of registers low byte
			crc = calculerCRC(request, 6);
			request[6] = (crc >> 8); // CRC high byte
			request[7] = crc & 0xFF; // CRC low byte
			com1->sendTx(request, 8);
			partage->setWait(true);
			while (partage->getWait() == true)
			{
				screen->dispStr(1, 15, "WAIT   ");
				usleep(10000); // Sleep for 10ms to avoid busy waiting
			}
			screen->dispStr(1, 15, "NO WAIT");
			ib = partage->getModbusValue();
			if (ib != partage->getIb())
			{
				partage->setIb(ib);
				ibValue = partage->getIb();
				sprintf(ibStr, "%.2f", ibValue);
				mqtt->publish(NULL, "RAM/powermeter/etats/Ib", strlen(ibStr), ibStr);
			}
			screen->dispStr(1, 6, "Ib : " + std::to_string(ibValue));
			break;

		case 5:
			// Modbus request format KWh
			request[0] = 0x02; // Slave address
			request[1] = 0x03; // Function code (Read Holding Registers)
			request[2] = 0x03; // High byte of address (fixed as 0x03)
			request[3] = 0x00; // Low byte of address
			request[4] = 0x00; // Number of registers high byte
			request[5] = 0x02; // Number of registers low byte
			crc = calculerCRC(request, 6);
			request[6] = (crc >> 8); // CRC high byte
			request[7] = crc & 0xFF; // CRC low byte
			com1->sendTx(request, 8);
			partage->setWait(true);
			while (partage->getWait() == true)
			{
				screen->dispStr(1, 15, "WAIT   ");
				usleep(10000); // Sleep for 10ms to avoid busy waiting
			}
			screen->dispStr(1, 15, "NO WAIT");
			kwh = partage->getModbusValue();
			if (kwh != partage->getKwh())
			{
				partage->setKwh(kwh);
				kwhValue = partage->getKwh();
				sprintf(kwhStr, "%.2f", kwhValue);
				mqtt->publish(NULL, "RAM/powermeter/etats/KWh", strlen(kwhStr), kwhStr);
			}
			screen->dispStr(1, 7, "KWh : " + std::to_string(kwhValue));
			break;

		case 6:
			// Modbus request format KW
			request[0] = 0x02; // Slave address
			request[1] = 0x03; // Function code (Read Holding Registers)
			request[2] = 0x03; // High byte of address (fixed as 0x03)
			request[3] = 0x02; // Low byte of address
			request[4] = 0x00; // Number of registers high byte
			request[5] = 0x02; // Number of registers low byte
			crc = calculerCRC(request, 6);
			request[6] = (crc >> 8); // CRC high byte
			request[7] = crc & 0xFF; // CRC low byte
			com1->sendTx(request, 8);
			partage->setWait(true);
			while (partage->getWait() == true)
			{
				screen->dispStr(1, 15, "WAIT   ");
				usleep(10000); // Sleep for 10ms to avoid busy waiting
			}
			screen->dispStr(1, 15, "NO WAIT");
			kw = partage->getModbusValue();
			if (kw != partage->getKw())
			{
				partage->setKw(kw);
				kwValue = partage->getKw();
				sprintf(kwStr, "%.2f", kwValue);
				mqtt->publish(NULL, "RAM/powermeter/etats/KW", strlen(kwStr), kwStr);
			}
			screen->dispStr(1, 8, "KW : " + std::to_string(kwValue));
			break;

		case 7:
			// Modbus request format FP
			request[0] = 0x02; // Slave address
			request[1] = 0x03; // Function code (Read Holding Registers)
			request[2] = 0x03; // High byte of address (fixed as 0x03)
			request[3] = 0x38; // Low byte of address
			request[4] = 0x00; // Number of registers high byte
			request[5] = 0x02; // Number of registers low byte
			crc = calculerCRC(request, 6);
			request[6] = (crc >> 8); // CRC high byte
			request[7] = crc & 0xFF; // CRC low byte
			com1->sendTx(request, 8);
			partage->setWait(true);
			while (partage->getWait() == true)
			{
				screen->dispStr(1, 15, "WAIT   ");
				usleep(10000); // Sleep for 10ms to avoid busy waiting
			}
			screen->dispStr(1, 15, "NO WAIT");
			fp = partage->getModbusValue();
			if (fp != partage->getFp())
			{
				partage->setFp(fp);
				fpValue = partage->getFp();
				sprintf(fpStr, "%.2f", fpValue);
				mqtt->publish(NULL, "RAM/powermeter/etats/FP", strlen(fpStr), fpStr);
			}
			screen->dispStr(1, 9, "FP : " + std::to_string(fpValue));
			break;

		default:
			break;
		}
		if (index < 7)
		{
			index++;
		}
		else
		{
			index = 0;
		}
		if (mqtt->loop(100) != 0)
			mqtt->reconnect();

	}
}
