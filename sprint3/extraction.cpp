// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <algorithm>
#include <typeinfo>

void outputDirectoryCreator();

using namespace std;

int main(int argc, char const *argv[])
{
    string inFileName;                                                               // Fichier en entrée
    ofstream outFile;                                                                // Fichier en sortie
    string line, title, abstract, reference, , introduction, discussion, conclusion; // Ligne lu
    string abstractSearch1 = "Abstract";
    string abstractSearch2 = "ABSTRACT";
    string abstractSearch3 = "abstract";
    string un = "1";
    string unBis = "I.";

    string referenceSearch1 = "\nReferences";
    string referenceSearch2 = "\nReferences";
    string referenceSearch3 = "\nReferences";

    string introductionSearch = "\nIntroduction";
    string DiscussionSearch = "\nDiscussion and Future Work";

    string conclusionSearch1 = "CONCLUSION";
    string conclusionSearch2 = "conclusion";
    string conclusionSearch3 = "Conclusion";

    bool endAbstract, endReference, endIntroduction, endDiscussion, endConclusion;

    outputDirectoryCreator();

    string arg1(argv[1]);

    cout << "entrer le nom du fichier: ";
    getline(cin, inFileName); // nom du fichier à traiter
    inFileName = inFileName;

    string ifStreamName = inFileName + ".txt";
    cout << "path du fichier: "
         << "pdftotext/" + ifStreamName << "\n";

    ifstream inFile("pdftotext/" + ifStreamName); // Ouverture du fichier en lecture

    if (inFile.is_open())
    {

        if (arg1 == "-t")
        {
            inFileName = inFileName + ".txt";
        }
        else if (arg1 == "-x")
        {
            inFileName = inFileName + ".xml";
        }

        outFile.open("extract/out" + inFileName, ios::out | ios::trunc); // Ouverture du fichier en écriture

        (getline(inFile, title)); // récupère la première ligne qu'on considère comme titre

        // Récupère l'abstract
        while (getline(inFile, line))
        {
            if (line.find(abstractSearch1) != string::npos ||
                line.find(abstractSearch2) != string::npos ||
                line.find(abstractSearch3) !=
                    string::npos)
            { // cherche dans line le pattern abstractSearch) { // cherche dans line le pattern abstractSearch
                cout << "\nfound referenceSearch1!\n ";
                while (!endAbstract)
                {
                    if (line.find(unBis) != string::npos || line.find(un) != string::npos)
                    {
                        endAbstract = true;
                        break;
                    }
                    abstract += line + " ";
                    getline(inFile, line);
                }
            }
            else
            {
                //                cout << "no abstract found, trying to found one" << endl;
            }
        }

        // Récupère les références
        while (getline(inFile, line))
        {
            if (line.find(referenceSearch1) != string::npos)
            { // cherche dans line le pattern abstractSearch
                cout << "\nfound referenceSearch1!\n ";
                while (!endReference)
                {
                    reference += line + " ";
                    if (!getline(inFile, line))
                    {
                        endReference = true;
                        break;
                    }
                }
            }
            else
            {
                //                cout << "no abstract found, trying to found one" << endl;
            }

            if (line.find(introductionSearch) != string::npos)
            { // cherche dans line le pattern abstractSearch
                cout << "\nfound introductionSearch!\n ";
                while (!endReference)
                {
                    introduction += line + " ";
                    if (!getline(inFile, line))
                    {
                        endReference = true;
                        break;
                    }
                }
            }
            else
            {
                //                cout << "no abstract found, trying to found one" << endl;
            }

            if (line.find(DiscussionSearch) != string::npos)
            { // cherche dans line le pattern abstractSearch
                cout << "\nfound DiscussionSearch!\n ";
                while (!endDiscussion)
                {
                    discussion += line + " ";
                    if (!getline(inFile, line))
                    {
                        endDiscussion = true;
                        break;
                    }
                }
            }
            else
            {
                //                cout << "no abstract found, trying to found one" << endl;
            }

            //Conclusion
            if (line.find(conclusionSearch1) != string::npos ||
                line.find(conclusionSearch2) != string::npos ||
                line.find(conclusionSearch3) != string::npos)
            { //
                cout << "\nfound Conclusion!\n ";
                while (!endConclusion)
                {
                    conclusion += line + " ";

                    if (line.find(referenceSearch1) ||
                        line.find(referenceSearch2) ||
                        line.find(referenceSearch3))
                    {
                        endConclusion = true;
                        break;
                    }
                }
            }
            else
            {
                cout << "no conclusion found, trying to found one" << endl;
            }
        }
    }
    else
    { // si erreur dans l'ouverture
        cout << "unable to locate file\n";
    }

    if (outFile.is_open())
    {
        //        cout << "filename : " + inFileName;
        //        cout << "\ntitre: " + title << '\n';

        if (arg1 == "-t")
        {
            cout << "format texte" << endl;
            outFile << inFileName << endl;
            outFile << title << endl;
            outFile << abstract;
        }
        else if (arg1 == "-x")
        {
            cout << "format xml" << endl;
            outFile << "<article>" << endl;
            outFile << "\t<preamble>" << inFileName << "</preamble>" << endl;
            outFile << "\t<titre>" << title << "</titre>" << endl;
            outFile << "\t<introduction>" << introduction << "</introduction>" << endl;
            outFile << "\t<auteur>"
                    << "La section auteurs et leur adresse"
                    << "</auteur>" << endl;
            outFile << "\t<abstract>" << abstract << "</abstract>" << endl;
            outFile << "\t<conclusion>" << conclusion << "</conclusion>" << endl;
            outFile << "\t<discussion>" << discussion << "</discussion>" << endl;
            outFile << "\t<biblio>" << reference << "</biblio>" << endl;
            outFile << "</article>" << endl;
        }
    }

    inFile.close();  // fermeture en entrée
    outFile.close(); // fermeture en entrée

    return 0;
}

/*
 * Create the directory for output.
 */
void outputDirectoryCreator()
{ // création repertoire en sortie
    if (mkdir("extract", 0777) == -1)
        cerr << "dossier déjà crée\n";
    else
        cout << "dossier crée\n";
}
