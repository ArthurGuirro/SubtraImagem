#include <opencv2/opencv.hpp> // Inclui a biblioteca OpenCV
#include <iostream>
#include <string>

using namespace cv; // Usar o namespace da OpenCV
using namespace std; // Usar o namespace padrão

// Função para exibir uma imagem em uma janela
void displayImage(const Mat& image, const string& windowName) {
    imshow(windowName, image); // Mostra a imagem na janela especificada
    waitKey(0); // Espera até que uma tecla seja pressionada
    destroyAllWindows(); // Fecha todas as janelas abertas
}

// Função para subtrair duas imagens
Mat subtractImages(const Mat& img1, const Mat& img2, float threshold) {
    // Cria uma Matriz vazia para armazenar o resultado da subtração
    Mat output = Mat::zeros(img1.size(), img1.type());

    // Laço para percorrer cada pixel das imagens
    for (int i = 0; i < img1.rows; ++i) {
        for (int j = 0; j < img1.cols; ++j) {
            Vec3b pixel1 = img1.at<Vec3b>(i, j); // Obtém o pixel da primeira imagem
            Vec3b pixel2 = img2.at<Vec3b>(i, j); // Obtém o pixel da segunda imagem

            // Calcula a diferença entre os canais de cor das duas imagens
            float red = static_cast<float>(pixel1[2]) - static_cast<float>(pixel2[2]);
            float green = static_cast<float>(pixel1[1]) - static_cast<float>(pixel2[1]);
            float blue = static_cast<float>(pixel1[0]) - static_cast<float>(pixel2[0]);

            // Verifica se o valor é negativo e ajusta para zero
            red = max(red, 0.0f);
            green = max(green, 0.0f);
            blue = max(blue, 0.0f);

            // Método básico (preto e branco): define o pixel de saída como preto (0,0,0) 
            // se a diferença for maior que o limiar ou branco (255,255,255) caso contrário
            output.at<Vec3b>(i, j) = (red > threshold || green > threshold || blue > threshold) ?
                Vec3b(0, 0, 0) : Vec3b(255, 255, 255);
        }
    }

    return output; // Retorna a imagem resultante da subtração
}

int main() {
    int option;

    while (true) {
        // Exibe um menu para o usuário escolher uma opção
        cout << "\n"
             << "Escolha\n"
             << "1- Subtrair Imagem\n"
             << "2- Sair do programa\n";

        cout << "Escolha: ";
        cin >> option;

        // Se o usuário escolher subtrair imagens
        if (option == 1) {
            string imageName1, imageName2;
            cout << "Digite o nome e a extensão da primeira imagem: ";
            cin >> imageName1;

            Mat img1 = imread(imageName1); // Lê a primeira imagem
            if (img1.empty()) {
                cerr << "Erro ao abrir a imagem: " << imageName1 << endl; // Verifica se a imagem foi carregada corretamente
                continue;
            }

            cout << "Digite o nome e a extensão da segunda imagem: ";
            cin >> imageName2;

            Mat img2 = imread(imageName2); // Lê a segunda imagem
            if (img2.empty()) {
                cerr << "Erro ao abrir a imagem: " << imageName2 << endl; // Verifica se a imagem foi carregada corretamente
                continue;
            }

            // Verifica se as duas imagens têm o mesmo tamanho
            if (img1.size() != img2.size()) {
                cerr << "As imagens devem ter o mesmo tamanho!" << endl;
                continue;
            }

            float threshold;
            cout << "Intensidade: ";
            cin >> threshold; // Solicita ao usuário o limiar de intensidade

            // Chama a função para subtrair as imagens
            Mat result = subtractImages(img1, img2, threshold);

            char saveOption;
            cout << "Salvar? S/N: ";
            cin >> saveOption; // Pergunta ao usuário se deseja salvar a imagem

            if (saveOption == 'S' || saveOption == 's') {
                string outputName;
                cout << "Nome da imagem (sem extensão): ";
                cin >> outputName; // Solicita o nome para salvar a imagem
                imwrite(outputName + ".jpg", result); // Salva a imagem resultante
                cout << "Sucesso!" << endl;
            }

            char displayOption;
            cout << "Ver imagem? S/N: ";
            cin >> displayOption; // Pergunta se o usuário deseja visualizar a imagem resultante

            if (displayOption == 'S' || displayOption == 's') {
                displayImage(result, "Imagem Subtraída"); // Exibe a imagem resultante
            }
        } else if (option == 2) {
            cout << "Fechando" << endl; // Mensagem de encerramento
            break; // Encerra o loop e sai do programa
        } else {
            cout << "Opção inserida é inválida, tente novamente!" << endl; // Mensagem de erro para opção inválida
        }
    }

    return 0; // Retorna 0 para indicar que o programa terminou corretamente
}
