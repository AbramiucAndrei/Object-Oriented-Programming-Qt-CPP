#include "repoReteta.hpp"
#include "repoException.h"
void RepoReteta::deleteAll() noexcept{
	reteta.clear();
}

void RepoReteta::addMed(const Medicament& new_med) {
    //auto search = findMedicament(new_med.getDenumire());
    //if(search!=reteta.end())
    //    throw RepoExp("Medicamentul exista deja in reteta")

	reteta.push_back(new_med);
}

//vector<Medicament>::iterator RepoReteta::findMedicament(const std::string& denumire) {
//    return std::find_if(reteta.begin(), reteta.end(), [=](const Medicament& medicament) {
//        return medicament.getDenumire() == denumire;
//        });
//}

void RepoReteta::Export(const string& file_name) {
    string filename = file_name;
    std::ofstream fout(filename);
    fout << "<html>\n"
        "<body>\n"
        "<head>\n"
        "    <h3 style=\" font-family: 'Caviar Dreams',serif; color:mediumpurple; \">Medicamente</h3>\n"
        "    </head>\n"
        "<style>\n"
        "    p {\n"
        "        color: #D7BDE2 ;\n"
        "        background-color: #A9CCE3 ;\n"
        "        border: 1px solid black; }\n"
        "    table,th,td{\n"
        "        border: 1px solid black;\n"
        "    }\n"
        "    th{\n"
        "        color: darkviolet;\n"
        "    }\n"
        "    body{\n"
        "        background-color: #CACFD2;\n"
        "    }\n"
        "</style>\n";
    fout << "<table>\n"
        "\n"
        "        <th>Name</th>\n"
        "        <th>Prod</th>\n"
        "        <th>Subst</th>\n"
        "        <th>Price</th>";
    for (const Medicament& med : getAll())
    {
        fout << "<tr>\n";
        fout << "<th>" << med.getDenumire() << "</th>\n"
            << "<th>" << med.getProducator() << "</th>\n"
            << "<th>" << med.getSubstActiva() << "</th>\n"
            << "<th>\n" << med.getPret() << "</th>\n"
            << "</tr>\n";


    }
    fout << "</table>\n"
        "\n"
        "\n"
        "</body>\n"
        "</html>";


}
