#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Função para gerar um número de cartão de crédito aleatório
long long generateCreditCardNumber() {
    long long cardNumber = 0;
    int numDigits = 16;

    // Gera os primeiros 15 dígitos do número do cartão de crédito
    for (int i = 0; i < numDigits - 1; i++) {
        cardNumber = cardNumber * 10 + (rand() % 10);
    }

    // Gera o último dígito (dígito de verificação) usando o algoritmo de Luhn
    int sum = 0;
    int doubleDigit = 0;
    long long tempCardNumber = cardNumber; // Armazena o número do cartão temporariamente
    for (int i = numDigits - 2; i >= 0; i--) {
        int digit = tempCardNumber % 10;
        tempCardNumber /= 10;

        if (doubleDigit) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        doubleDigit = !doubleDigit;
    }

    int checkDigit = (sum * 9) % 10;
    cardNumber = cardNumber * 10 + checkDigit;

    return cardNumber;
}

// Função para gerar um CVV aleatório de 3 dígitos
int generateCVV() {
    return rand() % 900 + 100;
}

// Função para gerar uma data de validade aleatória
void generateExpirationDate(int *month, int *year) {
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);

    *month = localTime->tm_mon + 1;  // O mês é baseado em zero, então adicionamos 1
    *year = localTime->tm_year + 1900;  // O ano é baseado em 1900

    // Adiciona um número aleatório de meses (entre 1 e 12) à data atual
    int numMonthsToAdd = rand() % 12 + 1;
    *month += numMonthsToAdd;

    // Se o mês for maior que 12, ajusta o mês e o ano
    if (*month > 12) {
        *month -= 12;
        *year += 1;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Gera um número de cartão de crédito, CVV e data de validade aleatórios
    long long cardNumber = generateCreditCardNumber();
    int cvv = generateCVV();
    int expirationMonth, expirationYear;
    generateExpirationDate(&expirationMonth, &expirationYear);

    // Imprime os resultados
    printf("Número do cartão de crédito: %lld\n", cardNumber);
    printf("CVV: %d\n", cvv);
    printf("Data de validade: %02d/%d\n", expirationMonth, expirationYear);

    return 0;
}