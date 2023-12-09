#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/*----------------------------------------------------------------------------------*/
// Funções de Fuzzificação
double CalcularMembroComidaRuim(double qualidadeComida) {
    if (qualidadeComida <= 2.0) return 1.0;
    else if (qualidadeComida <= 4.0) return (4.0 - qualidadeComida) / 2.0;
    else return 0.0;
}

double CalcularMembroComidaBoa(double qualidadeComida) {
    if (qualidadeComida <= 2.0 || qualidadeComida >= 8.0) return 0.0;
    else if (qualidadeComida <= 6.0) return (qualidadeComida - 2.0) / 4.0;
    else return (10.0 - qualidadeComida) / 2.0;
}

double CalcularMembroComidaOtima(double qualidadeComida) {
    if (qualidadeComida <= 6.0) return 0.0;
    else if (qualidadeComida <= 8.0) return (qualidadeComida - 6.0) / 2.0;
    else return 1.0;
}

double CalcularMembroServicoRuim(double qualidadeServico) {
    return exp(-0.5 * pow((qualidadeServico - 0.0) / 1.5, 2.0));
}

double CalcularMembroServicoBom(double qualidadeServico) {
    return exp(-0.5 * pow((qualidadeServico - 5.0) / 2.5, 2.0));
}

double CalcularMembroServicoOtimo(double qualidadeServico) {
    return exp(-0.5 * pow((qualidadeServico - 10.0) / 2.5, 2.0));
}

/*----------------------------------------------------------------------------------*/
// Funções de Inferência
double CalcularGorjetaBaixa(double servicoRuim, double comidaRuim) {
    return fmax(servicoRuim, comidaRuim);
}

double CalcularGorjetaMedia(double servicoBom) {
    return servicoBom;
}

double CalcularGorjetaAlta(double servicoOtimo, double comidaOtima) {
    return fmax(servicoOtimo, comidaOtima);
}

/*----------------------------------------------------------------------------------*/
// Funções de Defuzzificação
double DefuzzCentroide(double gorjetaBaixa, double gorjetaMedia, double gorjetaAlta) {
    double numerador = gorjetaBaixa * 5.0 + gorjetaMedia * 15.0 + gorjetaAlta * 25.0;
    double denominador = gorjetaBaixa + gorjetaMedia + gorjetaAlta;
    return numerador / denominador;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    double qualidadeComida, qualidadeServico;

    //Entrada
    cout << "Avalie a comida (0 a 10): ";
    cin >> qualidadeComida;
    cout << "Avalie o serviço (0 a 10): ";
    cin >> qualidadeServico;

    // Fuzzificação
    double comidaRuim = CalcularMembroComidaRuim(qualidadeComida);
    double comidaBoa = CalcularMembroComidaBoa(qualidadeComida);
    double comidaOtima = CalcularMembroComidaOtima(qualidadeComida);

    double servicoRuim = CalcularMembroServicoRuim(qualidadeServico);
    double servicoBom = CalcularMembroServicoBom(qualidadeServico);
    double servicoOtimo = CalcularMembroServicoOtimo(qualidadeServico);

    // Inferência
    double gorjetaBaixa = CalcularGorjetaBaixa(servicoRuim, comidaRuim);
    double gorjetaMedia = CalcularGorjetaMedia(servicoBom);
    double gorjetaAlta = CalcularGorjetaAlta(servicoOtimo, comidaOtima);

    // Defuzzificação
    double porcentagemGorjeta = DefuzzCentroide(gorjetaBaixa, gorjetaMedia, gorjetaAlta);

    //Saída
    cout << fixed << setprecision(2);
    cout << "Porcentagem de gorjeta recomendada: " << porcentagemGorjeta << "%" << endl; 

    return 0;
}
