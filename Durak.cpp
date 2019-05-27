#include<iostream>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include <algorithm>//���������� ��� ������������� ����
using namespace std;
enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void SetCursor(int x, int y)
{
	COORD myCoords = { x,y };//��������� ��� �������� ���������
	SetConsoleCursorPosition(hStdOut, myCoords);//������� ������������� ������ �� ���� �������
}
int x = 1, y = 1;//����������
//������ ��� ��������
const int lengthNominal = 9;
char nominal[lengthNominal] = { '6', '7', '8', '9', '0', 'B', 'D', 'K', 'A' };
//������ ��� �����
const int lengthMast = 4;
char mast[lengthMast] = { 3, 4, 5, 6 };
char kozir = ' ';
const int row = 9, col = 9;
char mas[row][col] =
//����� �������������
{ { 218, 196, 196, 196, 196, 196, 196,196,191 },
{ 179, ' ', ' ',' ',' ',' ',' ',' ',179 },
{ 179, ' ',' ',' ',' ',' ',' ',' ',179 },
{ 179, ' ',' ',' ',' ',' ',' ',' ',179 },
{ 179, ' ',' ',' ',' ',' ',' ',' ',179 },
{ 179, ' ',' ',' ',' ',' ',' ',' ',179 },
{ 179, ' ',' ',' ',' ',' ',' ',' ',179 },
{ 179, ' ',' ',' ',' ',' ',' ',' ',179 },
{ 192,196, 196, 196, 196, 196, 196,196,217 } };
int giveCardFromColoda = 0;
struct myCard {
	char nominal;
	char mast;
	int znachimostNominala;
};
//��� ������ ����������� ��������� � ������.
void setColoda(myCard *allColoda, int length)
{
	int z = 0;
	char m = 0;
	for (int i = 0; i < length; i++)
	{
		allColoda[i].nominal = z;
		allColoda[i].znachimostNominala = z;
		z++;
		allColoda[i].mast = m;
		if (m == 4)
		{
			m = 0;
		}
		if (z == 9)
		{
			z = 0;
			m++;
		}
	}
}
//���������� ���� ������� �� ������
myCard *fillCard(myCard *allColoda, myCard *player, int lengthPlayer) {

	player = new myCard[lengthPlayer];
	for (size_t i = 0; i < lengthPlayer; i++) {
		player[i] = allColoda[giveCardFromColoda];
		giveCardFromColoda++;
	}
	return player;
}
//����� ����
void showCard(myCard allColoda, int pozX, int pozY) {
	x = pozX;
	y = pozY;
	for (int i = 0; i < row; i++)
	{
		SetCursor(x, y + i);
		for (int j = 0; j < col; j++)
		{
			if (((i == 1 && j == 1) && allColoda.nominal == 4) || (i == 7 && j == 6 && allColoda.nominal == 4))
			{
				cout << 1;
			}
			else if ((i == 1 && j == 1) || (i == 7 && j == 7))
			{
				cout << nominal[allColoda.nominal];
			}
			else if (((i == 1 && j == 2) && allColoda.nominal == 4) || (i == 7 && j == 6 && allColoda.nominal == 4))
			{
				cout << nominal[allColoda.nominal];
			}
			else if ((i == 2 && j == 2) || i == 6 && j == 6)
			{
				if (mast[allColoda.mast] == 4 || mast[allColoda.mast] == 3)
				{
					setColor(Red, White);
					cout << mast[allColoda.mast];
				}
				else {
					setColor(Black, White);
					cout << mast[allColoda.mast];
				}
			}
			else {
				setColor(Black, White);
				cout << mas[i][j];
			}
		}
		cout << endl;
	}
	setColor(White, Black);
};
//����� ���� � "��������"
void showCardBot(myCard allColoda, int pozX, int pozY) {
	x = pozX;
	y = pozY;
	for (int i = 0; i < row; i++)
	{
		SetCursor(x, y + i);
		for (int j = 0; j < col; j++)
		{
			if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
			{
				setColor(Black, White);
				cout << mas[i][j];
			}
			else if (i % 2 != 0)
			{
				setColor(White, Cyan);
				cout << mas[i][j];
			}
			else
			{
				setColor(White, White);
				cout << mas[i][j];

			}
		}
		cout << endl;
	}
	setColor(White, Black);
};
//�������� ��� ����� ������� �� ������
void show(myCard * userCard, int length, int key) {
	if (key == 1)
	{
		x = 1;
		y = 2;
		for (size_t i = 0; i < length; i++) {
			showCard(userCard[i], x, y);
			x += 10;
		}
	}
	else if (key == 2)
	{
		x = 1;
		y = 40;
		for (size_t i = 0; i < length; i++) {
			showCardBot(userCard[i], x, y);
			x += 10;
		}
	}
}
//"��������" ����� �� ����� ���� �� �����
void show(myCard * stolCard, int length) {
	x = 1;
	y = 14;
	for (size_t i = 0; i < length; i++) {

		showCard(stolCard[i], x, y);
		if (i % 2 == 0)
		{
			x += 5;
		}
		else
		{
			x += 10;
		}
	}
}
//"����������" ���� ��������� ����� 
void show(int whichCarta, myCard * userCard, int pozY, int pozX = x) {
	x = pozX;
	y = pozY;
	showCard(userCard[whichCarta], x, y);
}
//������ �����
void black() {
	setColor(Black, Black);
	for (int i = 0; i < 10; i++)
	{
		SetCursor(x, y + i);
		for (int j = 0; j < 10; j++)
		{
			cout << mas[i][j];
		}
		cout << endl;
	}
	setColor(White, Black);
}
//"������������" ���� ������� � �����
void cliner(int pozX, int pozY, int length) {
	SetCursor(pozX, pozY);
	for (int i = 0; i < 10; i++)
	{
		SetCursor(pozX, pozY + i);
		for (int j = 0; j < length * 14; j++)
		{
			cout << " ";
		}
		cout << endl;
	}
}
//��� ����� ������
int First(myCard* user, myCard* bot) {
	int minUser = 10, minBot = 10, who;
	for (size_t i = 0; i < 6; i++)
	{
		if (user[i].znachimostNominala < minUser && mast[user[i].mast] == kozir) {
			minUser = user[i].znachimostNominala;
		}
		if (bot[i].znachimostNominala < minBot && mast[bot[i].mast] == kozir) {
			minBot = bot[i].znachimostNominala;
		}
	}
	if (minUser < minBot) {
		who = -1;
	}
	else if (minUser > minBot) {
		who = 1;
	}
	else {
		who = rand() % 2;
		if (who == 1)
		{
			who = -1;
		}
		else {
			who = 1;
		}
	}
	return who;
}
//������ �����������
void copyAll(myCard * const from, myCard * whereAre, int length) {
	for (int i = 0; i < length; i++)
	{
		whereAre[i] = from[i];
	}
}
//����������� ���� ������ ��� �������� �� ����
myCard * copyPlayer(myCard * const from, myCard * whereAre, int length, int whichCard) {
	for (int i = 0; i < length; i++)
	{
		if (i < whichCard)
		{
			whereAre[i] = from[i];
		}
		else if (i >= whichCard)
		{
			whereAre[i] = from[i + 1];
		}
	}
	return whereAre;
}
//��� �������(������ �� "�����" ���� �� ����)
myCard * move(myCard * const userCard, myCard * stolCard, int &lengthStol, int whichCarta, int kolKartNaStole = 0) {
	int lengthBuf;
	lengthBuf = lengthStol;
	myCard *buf = new myCard[lengthBuf];//�������� ������ �����
	copyAll(stolCard, buf, lengthBuf);//����������� ������ ��������
	delete[]stolCard;
	lengthStol++;//��������� ���� �� 1
	stolCard = new myCard[lengthStol];
	copyAll(buf, stolCard, lengthStol);//����������� ������ ��������

	for (int i = 0; i < lengthStol - kolKartNaStole; i++)
	{
		stolCard[i + kolKartNaStole] = userCard[whichCarta];
	}
	delete[]buf;
	return stolCard;
}
//������ �������� ����� �� ���� �� ���� ������
myCard * minusUserCard(myCard * userCard, int &length, int whichCarta) {
	int lengthBuf;
	lengthBuf = length;
	myCard *buf = new myCard[lengthBuf];//�������� ������ ������
	copyAll(userCard, buf, lengthBuf);//����������� ������ ��������
	delete[]userCard;
	length -= 1;//�������� ������ ���� � ���� �� 1
	userCard = new myCard[length];
	userCard = copyPlayer(buf, userCard, length, whichCarta);//����� �����
	delete[]buf;
	return userCard;
}
//����� ����� �� �����, ���� ����� ��� �� ������ ����
myCard * takeFromTable(myCard * userCard, myCard * stolKard, int &length, int kolKartNaStole) {
	int lengthBuf;
	lengthBuf = length;
	myCard *buf = new myCard[lengthBuf];//�������� ������ ������
	copyAll(userCard, buf, lengthBuf);//����������� ������ ��������
	delete[]userCard;
	length += kolKartNaStole;//�������� ������ ���� � ���� �� 1
	userCard = new myCard[length];
	copyAll(buf, userCard, lengthBuf);//����������� ������ ��������
	for (int i = lengthBuf, j = 0; i < length; i++)
	{
		userCard[i] = stolKard[j];
		j++;
	}
	delete[]buf;
	return userCard;
}
//������������ ������ ���� �� ����� ��������� 
myCard * clearTable(myCard * tableKard, int &length) {
	delete[]tableKard;
	length = 0;
	tableKard = new myCard[length];
	return tableKard;
}
//������ ���� �� ������
myCard *fillCardPlayers(myCard *allColoda, myCard *player, int& lengthPlayer) {
	int lengthBuf, kolKartlength = 6;
	lengthBuf = lengthPlayer;
	myCard *buf = new myCard[lengthBuf];//�������� ������ 
	copyAll(player, buf, lengthBuf);//����������� ������ ��������
	delete[]player;
	if ((lengthPlayer + (36 - giveCardFromColoda)) >= 6)//�������� ������� �� ���� �� ������ ��� ����, ���� ������ �����(��������, 4 + 6 = 10) 10 > 6, ����� ������ �����
	{
		lengthPlayer = 6;
	}
	else if ((lengthPlayer + (36 - giveCardFromColoda)) < 6)//���� � ������ �� ������� ��� ������(�������� 4 + 1 = 5) 5 < 6, �� �������
	{
		lengthPlayer += (36 - giveCardFromColoda);// ������ ������ ������� ���� ����� ����� 4 + 1 = 5
	}

	player = new myCard[lengthPlayer];
	copyAll(buf, player, lengthBuf);//����������� ������ ��������

	for (size_t i = 0; i < lengthPlayer - lengthBuf; i++) {
		player[i + lengthBuf] = allColoda[giveCardFromColoda];
		giveCardFromColoda++;
	}
	return player;
}
//��������, ����� �� ������ ������
bool canGive�ard(int lengthTable, myCard * userCard, myCard * stolCard, int length, int whichCarta) {

	if (lengthTable == 0)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < length + 1; i++)
		{
			if (nominal[userCard[whichCarta].nominal] == nominal[stolCard[i].nominal])
			{
				return true;
			}
		}
	}
	return false;
}
//��������, ����� �� ������ ����
bool canGiveCard(myCard * bot, myCard * tableCard, int lengthBot, int lengthTable, int &whichCarta, int kozirna) {

	for (int i = 0; i < lengthBot; i++)
	{
		for (int j = 0; j < lengthTable; j++)
		{
			if (nominal[bot[i].nominal] == nominal[tableCard[j].nominal] && mast[bot[i].mast] != kozirna)
			{
				whichCarta = i;
				return true;
			}
		}
	}
	for (int i = 0; i < lengthBot; i++)
	{
		for (int j = 0; j < lengthTable; j++)
		{
			if (nominal[bot[i].nominal] == nominal[tableCard[j].nominal])
			{
				whichCarta = i;
				return true;
			}
		}
	}
	return false;
}
//��������, ����� �� ������
bool canGiveCardBack(myCard * userCard, myCard * tableCard, int lengthTable, int whichCarta, char kozirna) {

	if ((userCard[whichCarta].znachimostNominala > tableCard[lengthTable - 1].znachimostNominala) && mast[tableCard[lengthTable - 1].mast] == mast[userCard[whichCarta].mast])
	{
		return true;
	}
	else if (mast[userCard[whichCarta].mast] == kozirna && mast[tableCard[lengthTable - 1].mast] != kozirna)
	{
		return true;
	}
	else if (mast[userCard[whichCarta].mast] == kozirna && mast[tableCard[lengthTable - 1].mast] == kozirna && userCard[whichCarta].znachimostNominala > tableCard[lengthTable - 1].znachimostNominala)
	{
		return true;
	}
	return false;
}
//�������� ��������� �����
int litle(myCard * bot, int lengthBot, char kozirna) {
	int min = bot[0].znachimostNominala;
	int poz = -1;
	for (int i = 0; i < lengthBot; i++)
	{
		if ((bot[i].znachimostNominala < min) && (mast[bot[i].mast] != kozirna))
		{
			min = bot[i].znachimostNominala;
			poz = i;
		}
	}
	if (poz == -1)
	{
		poz = 0;
		for (int i = 0; i < lengthBot; i++)
		{
			if ((bot[i].znachimostNominala < min) && (mast[bot[i].mast] == kozirna))
			{
				min = bot[i].znachimostNominala;
				poz = i;
			}
		}

	}
	return poz;

}
//����� �����, ������� ����� �������
int choiseCard(myCard * user, int lengthUser, int whichCard) {
	int input;
	int i = 0;
	x = 1, y = 2;
	SetCursor(1, 1);
	do
	{
		if (lengthUser != 0)
		{
			black();
			show(whichCard, user, 1);
		}
		input = _getch();//���������� ������� ������
		switch (input)
		{
		case 75://������� �����
			if (x < 2)
			{
				break;
			}
			else
			{
				whichCard--;
				black();
				show(whichCard + 1, user, 2);
				x -= 10;
				black();
				show(whichCard, user, 1);
				break;
			}
		case 77://������� ������
			if (x >= (lengthUser - 1) * 10)
			{
				break;
			}
			else
			{
				whichCard++;
				black();
				show(whichCard - 1, user, 2);
				x += 10;
				black();
				show(whichCard, user, 1);
				break;
			}
		case 13:// enter
			return whichCard;//���� ������� �����, ������� ������
			break;
		case 32://������
			i = -1;
			return i;//���� ������� �����, ������� ������

			break;
		}
	} while (true);
}
//"�����" ����, ��� ������ ���
int giveCardBackBot(myCard * bot, myCard * stol, int lengthBot, int lengthTable) {
	int pozOtbil = -1;
	//���� ����� ������ �� ������� ���������� ������� ���� �����
	for (int i = 0; i < lengthBot; i++)
	{
		if ((mast[bot[i].mast] == mast[stol[lengthTable - 1].mast]) && (bot[i].znachimostNominala > stol[lengthTable - 1].znachimostNominala))
		{
			pozOtbil = i;
			break;
		}
	}
	//�� ������ ������ ��� ������, ���� ������
	if (pozOtbil == -1)
	{
		for (int i = 0; i < lengthBot; i++)
		{
			if (mast[bot[i].mast] == kozir && mast[stol[lengthTable - 1].mast] != kozir)
			{
				pozOtbil = i;
				break;
			}
			else if (mast[bot[i].mast] == kozir && mast[stol[lengthTable - 1].mast] == kozir && bot[i].znachimostNominala > stol[lengthTable - 1].znachimostNominala)
			{
				pozOtbil = i;
				break;
			}
		}
	}
	return pozOtbil;

}
int moveBot = 0;//��� ����
int pozCardBackBot = -1;//����� ������ ������� ���
int whichCard = 0;//����� ������ ������ �����
int testMoveUser = 0;//����� ����� �������� ������ ��� ���(��� do while)
void forPlay() {
	SetCursor(111, 21);
	if (36 - giveCardFromColoda <= 9)
	{
		setColor(Cyan, Cyan);
		cout << "  ";
		setColor(White, Black);
	}
	setColor(Black, Cyan);
	cout << 36 - giveCardFromColoda;
	setColor(White, Black);
	moveBot = 0;//��� ����
	pozCardBackBot = -1;//����� ������ ������� ���
	whichCard = 0;//����� ������ ������ �����
	testMoveUser = 0;//����� ����� �������� ������ ��� ���(��� do while)

	if (36 - giveCardFromColoda == 0)
	{
		x = 100; y = 20;
		black();
		x = 110; y = 20;
		black();
	}
}
void main() {
	srand(time(NULL));

	cout << "\n\tWelcome to FOOL\n\n\n\n RULES:\n\n ENTER - choice card\n\n Space - Take card / hang-up\n\n Left <-\n\n Right ->\n\n\n\n";//�����
	cout << " Press 'esc' to exit or press any key to play\n\n";
	int exitPlayer;
	exitPlayer = _getch();//���������� ������� ������
	switch (exitPlayer)
	{
	case 27://������� �����
		cout << "Good bye\n\n";
		exit(0);
		system("pause");
		break;
	}
	system("cls");
	int const lengthColoda = 36;
	int lengthUser = 6, lengthBot = 6, lengthTable = 0;
	int kolKartUser = 0, kolKartBot = 0;
	myCard *userCards = new myCard[lengthUser];//������������ ������ ���� � ������
	myCard *botCards = new myCard[lengthBot];//������������ ������ ���� � ������
	myCard *tableCard = new myCard[lengthTable];//������������ ������ ���� � ������
	myCard allColoda[lengthColoda];//����� ���� � ������
	setColoda(allColoda, lengthColoda);//�������� ������
	random_shuffle(allColoda, allColoda + lengthColoda);// ���������� ������! ������ �� ������� � ��������� : http://www.cyberforum.ru/cpp-beginners/thread624310.html
	kozir = mast[allColoda[35].mast];//�������� ������
	userCards = fillCard(allColoda, userCards, lengthUser - kolKartUser);//����� ����� ������
	botCards = fillCard(allColoda, botCards, lengthBot - kolKartBot);//����� ����� ����
	int whosTurn;
	whosTurn = First(userCards, botCards);//���� ������ 0 ����� user, ���� ������ 0 ����� ���
	do
	{
		if (36 - giveCardFromColoda > 0)
		{
			show(lengthColoda - 1, allColoda, 20, 100);
			showCardBot(allColoda[0], 110, 20);
		}
		show(userCards, lengthUser, 1);//������� ����� ������
		show(botCards, lengthBot, 2);//������� ����� ����
		forPlay();//���������� whichCard, pozCardBackBot, moveBot
		if (whosTurn < 0)// ����� �����
		{
			whichCard = choiseCard(userCards, lengthUser, whichCard);//����� ����� ��� ����
			if (lengthTable > 0 && whichCard < 0)//�����, ������� ���� � ����
			{
				black();
				cliner(1, 13, lengthTable + 1);//������������ ���� �� �����
				tableCard = clearTable(tableCard, lengthTable);//���� �� ����� 0
				if ((36 - giveCardFromColoda) > 0)
				{

					if (lengthUser < 6)
					{
						userCards = fillCardPlayers(allColoda, userCards, lengthUser);//������������ ���� ������ �� ���� ������
						cliner(1, 2, lengthUser + 1);//������������ ������
						show(userCards, lengthUser, 1);//������� ����� ������
					}
					if (lengthBot < 6)
					{
						botCards = fillCardPlayers(allColoda, botCards, lengthBot);//������������ ���� ������ �� ���� ������
						cliner(1, 40, lengthBot + 1);//������������ ���� �� �����
						show(botCards, lengthBot, 2);//������� ����� ������
					}
				}
				whosTurn = 1;
				continue;
			}
			else if (lengthTable == 0 && whichCard < 0)
			{
				black();
				continue;
			}
			if (canGive�ard(lengthTable, userCards, tableCard, lengthUser, whichCard) == true)//�������� ����� �� ������
			{
				black();
				tableCard = move(userCards, tableCard, lengthTable, whichCard, lengthTable);//����� �� �����
				userCards = minusUserCard(userCards, lengthUser, whichCard);//����� ������
				cliner(1, 2, lengthUser + 1);//������������ ���� ������ � ������
				show(tableCard, lengthTable);//������� ����� ������
				show(userCards, lengthUser, 1);//������� ����� ������
				Sleep(700);
			}
			//���� ����� ����� ��������� �����, ������� ��� �� �����
			else {
				black();
				continue;
			}
			pozCardBackBot = giveCardBackBot(botCards, tableCard, lengthBot, lengthTable);//����� ������� ��� ����� ������(���� �� -1)
			if (pozCardBackBot >= 0)
			{
				tableCard = move(botCards, tableCard, lengthTable, pozCardBackBot, lengthTable);//����� �� �����
				botCards = minusUserCard(botCards, lengthBot, pozCardBackBot);//����� ������
				cliner(1, 40, lengthBot + 1);//������������ ���� �� �����
				cliner(1, 13, lengthTable + 1);//������������ ���� �� �����
				show(tableCard, lengthTable);//������� ����� ������
				show(botCards, lengthBot, 2);//������� ����� ������
			}
			//���� ���� ����� ����
			else if (pozCardBackBot == -1)
			{
				Sleep(700);
				botCards = takeFromTable(botCards, tableCard, lengthBot, lengthTable);
				cliner(1, 13, lengthTable + 1);//������������ ���� �� �����
				cliner(1, 40, lengthBot + 1);//������������ ���� ����
				tableCard = clearTable(tableCard, lengthTable);//���� �� ����� 0
				show(botCards, lengthBot, 2);//������� ����� ������
				if ((36 - giveCardFromColoda) > 0)
				{

					if (lengthUser < 6)
					{
						userCards = fillCardPlayers(allColoda, userCards, lengthUser);//������������ ���� ������ �� ���� ������
						cliner(1, 2, lengthUser + 1);//������������ ������
						show(userCards, lengthUser, 1);//������� ����� ������
					}
					if (lengthBot < 6)
					{
						botCards = fillCardPlayers(allColoda, botCards, lengthBot);//������������ ���� ������ �� ���� ������
						cliner(1, 40, lengthBot + 1);//������������ ���� �� �����
						show(botCards, lengthBot, 2);//������� ����� ������
					}
				}
			}
		}
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (whosTurn > 0)//����� ���
		{
			Sleep(800);
			//������ ��� ����
			if (lengthTable == 0)
			{
				moveBot = litle(botCards, lengthBot, kozir);
				tableCard = move(botCards, tableCard, lengthTable, moveBot, lengthTable);//����� �� �����
				botCards = minusUserCard(botCards, lengthBot, moveBot);//����� ������
				cliner(1, 40, lengthBot + 1);//������������ ���� ������ � ������
				show(tableCard, lengthTable);//������� ����� ������
				show(botCards, lengthBot, 2);//������� ����� ������
			}
			//��� ���������� �����, ���� �����
			else {
				if (canGiveCard(botCards, tableCard, lengthBot, lengthTable, moveBot, kozir) == true)
				{
					tableCard = move(botCards, tableCard, lengthTable, moveBot, lengthTable);//����� �� �����
					botCards = minusUserCard(botCards, lengthBot, moveBot);//����� ������
					cliner(1, 40, lengthBot + 1);//������������ ���� ������ � ������
					show(tableCard, lengthTable);//������� ����� ������
					show(botCards, lengthBot, 2);//������� ����� ������
				}
				//��� ���� ������ ��������� ����� ����� �� ������ �� ���������� � ��� ������
				else {
					cliner(1, 13, lengthTable + 1);//������������ ���� �� �����
					tableCard = clearTable(tableCard, lengthTable);//���� �� ����� 0
					if ((36 - giveCardFromColoda) > 0)
					{
						if (lengthUser < 6)
						{
							userCards = fillCardPlayers(allColoda, userCards, lengthUser);//������������ ���� ������ �� ���� ������
							cliner(1, 2, lengthUser + 1);//������������ ������
							show(userCards, lengthUser, 1);//������� ����� ������
						}
						if (lengthBot < 6)
						{
							botCards = fillCardPlayers(allColoda, botCards, lengthBot);//������������ ���� ������ �� ���� ������
							cliner(1, 40, lengthBot + 1);//������������ ���� �� �����
							show(botCards, lengthBot, 2);//������� ����� ������
						}
					}
					whosTurn = -1;
					continue;
				}
			}
			do
			{
				whichCard = choiseCard(userCards, lengthUser, whichCard);//����� ����� ��� ����
				//������� �����, ������ ������
				if (whichCard < 0)
				{
					black();
					userCards = takeFromTable(userCards, tableCard, lengthUser, lengthTable);
					cliner(1, 13, lengthTable + 1);//������������ ���� �� �����
					cliner(1, 2, lengthUser + 1);//������������ ���� ������
					tableCard = clearTable(tableCard, lengthTable);//���� �� ����� 0
					show(userCards, lengthUser, 1);//������� ����� ������
					if ((36 - giveCardFromColoda) > 0)
					{
						if (lengthUser < 6)
						{
							userCards = fillCardPlayers(allColoda, userCards, lengthUser);//������������ ���� ������ �� ���� ������
							cliner(1, 2, lengthUser + 1);//������������ ������
							show(userCards, lengthUser, 1);//������� ����� ������
						}
						if (lengthBot < 6)
						{
							botCards = fillCardPlayers(allColoda, botCards, lengthBot);//������������ ���� ������ �� ���� ������
							cliner(1, 40, lengthBot + 1);//������������ ���� �� �����
							show(botCards, lengthBot, 2);//������� ����� ������
						}
					}
					break;
				}
				//��������, ���� ����� �����
				if (canGiveCardBack(userCards, tableCard, lengthTable, whichCard, kozir) == true)
				{
					tableCard = move(userCards, tableCard, lengthTable, whichCard, lengthTable);//����� �� �����
					userCards = minusUserCard(userCards, lengthUser, whichCard);//����� ������
					cliner(1, 1, lengthUser + 1);//������������ ���� ������
					cliner(1, 13, lengthTable + 1);//������������ ���� �� �����
					show(tableCard, lengthTable);//������� ����� ������
					show(userCards, lengthUser, 1);//������� ����� ������
					testMoveUser = 1;
				}
				//���� ������ ����� ����� �������� ������, ������� ������(�����)
				else
				{
					black();
					show(userCards, lengthUser, 1);//������� ����� ������
					whichCard = 0;
					continue;
				}
			} while (testMoveUser != 1);
		}
		if ((lengthUser == 0 && (36 - giveCardFromColoda) == 0) || (lengthBot == 0 && (36 - giveCardFromColoda) == 0) || ((lengthUser == 0 && lengthBot == 0 && (36 - giveCardFromColoda) == 0)))
		{
			Sleep(1500);
			setlocale(LC_ALL, "rus");
			system("cls");
			SetCursor(20, 20);
			if (lengthBot == 0 && lengthUser == 0)
			{
				cout << "�����, �� ���������� ����, ���� ������";
			}
			else if (lengthUser == 0)
			{
				cout << "�� ��������!!!!" << endl;
			}
			else if (lengthBot == 0)
			{
				cout << "���������" << endl;
			}
			setColor(Black, Black);
			break;
		}
	} while (true);
	system("pause");
}