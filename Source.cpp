#include <Windows.h>
#include <iostream>

using namespace std;
int main() {

	int BaseAddress = 0x002D08B0;
	int currentValue;
	HWND hWND = FindWindow(NULL, "PickGame"); //Find Window name
	int buffer = 100;

		while(hWND == NULL) {
		hWND = FindWindow(NULL, "PickGame");
		cout << "Still searching for the game..";

		Sleep(1000); //Reduce the consume of CPU
		system("cls");
	}
	DWORD pID;


	if (!GetWindowThreadProcessId(hWND, &pID)) {

		cout << "Cant get ProcessId! ";
	}

	HANDLE hndl = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

	if (!hndl) {
		cout << "We cant OpenProcess for the desired Process ID! " << endl;
	}
	cout << "We have Obtained Handle and we are ready to start the cheat :) press TAB to increase the cash! " <<endl;
	
	ReadProcessMemory(hndl, (LPVOID)BaseAddress, &currentValue, sizeof(currentValue), 0); //Read the current value from the base address in memory

	cout << "Our current cash is: " << currentValue << endl;

	for (;;) {
		
		Sleep(1000);

		if (GetAsyncKeyState(VK_TAB)) { //when pressing on TAB button , it will increase the amount of cash to +100
			cout << "Trying to increase the cash now..." << endl;

			if (WriteProcessMemory(hndl, (LPVOID)BaseAddress, &buffer, sizeof(buffer), 0)) {
			
			ReadProcessMemory(hndl, (LPVOID)BaseAddress, &currentValue, sizeof(currentValue), 0);

			cout << "Our current cash is: " << currentValue << endl;
			buffer +=100;
			Sleep(1000);
			}
			else {
				cout << "Something is wrong , cant increase the cash!" << endl;
				ReadProcessMemory(hndl, (LPVOID)BaseAddress, &currentValue, sizeof(currentValue), 0); //Now reading the new value

				cout << "Our current cash is: " << currentValue << endl;
				Sleep(700);
			}
		}
	}
		

			Sleep(10);
		
		
	
	return 0;
}
