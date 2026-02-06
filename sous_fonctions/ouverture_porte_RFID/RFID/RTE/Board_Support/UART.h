// Bibliothèque UART - IUT de Cachan
// Avril 2022

#define	SANS			0x00
#define	IMPAIRE		0x01
#define PAIRE			0x02

void initUART1 (char parite);
void envoiUART1 (char donnee);
char recepUART1 (void);
