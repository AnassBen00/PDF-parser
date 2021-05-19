// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <algorithm>

void outputDirectoryCreator();

using namespace std;

int main(int argc, char const *argv[]) {
    string inFileName;        // Fichier en entrée
    ofstream outFile;    // Fichier en sortie
    string line, title, abstract;    // Ligne lu
    string abstractSearch1 = "Abstract";
    string abstractSearch2 = "ABSTRACT";
    string abstractSearch3 = "abstract";
    string un = "1";
    string unBis = "I.";
    bool endAbstract;

    outputDirectoryCreator();


    cout << "entrer le nom du fichier: ";
    getline(cin, inFileName); // nom du fichier à traiter

    cout << "path du fichier: " << "pdftotext/" + inFileName << "\n";

    ifstream inFile("pdftotext/" + inFileName);    // Ouverture du fichier en lecture
    if (inFile.is_open()) {

        outFile.open("extract/out" + inFileName, ios::out | ios::trunc); // Ouverture du fichier en écriture

        (getline(inFile, title));   // récupère la première ligne qu'on considère comme titre

        while (getline(inFile, line)) {
            if (line.find(abstractSearch1) != string::npos ||
                    line.find(abstractSearch2) != string::npos ||
                    line.find(abstractSearch3) != string::npos ) { // cherche dans line le pattern abstractSearch
                cout << "\nfound abstractSearch!\n ";
                while (!endAbstract) {
                    if (line.find(unBis) != string::npos || line.find(un) != string::npos) {
                        endAbstract = true;
                        break;
                    }
                    abstract += line + " ";
                    getline(inFile, line);
                }
            } else {
                cout << "no abstract found, trying to found one" << endl;

            }
        }
    } else {    // si erreur dans l'ouverture
        cout << "unable to locate file\n";
    }


    if (outFile.is_open()) {
        cout << "filename : " + inFileName;
        cout << "\ntitre: " + title << '\n';

        outFile << inFileName << endl;
        outFile << title << endl;
        outFile << abstract;
    }


    inFile.close();                        // fermeture en entrée
    outFile.close();                       // fermeture en entrée


    return 0;
}

/*
 * Create the directory for output.
 */
void outputDirectoryCreator() {// création repertoire en sortie
    if (mkdir("extract", 0777) == -1)
        cerr << "dossier déjà crée\n";
    else
        cout << "dossier crée\n";
}
