#include "Service.hpp"

#include <fstream>
#include <algorithm>
#include <random>

Service::Service(AbstractFarmacy &farmacy, Recipe &recipe) : farmacy{farmacy}, recipe{recipe} {
    std::ofstream html("../database/export.html");
    html.close();

    std::ofstream csv("../database/export.csv");
    csv.close();
}

std::vector<Medicament> Service::getAllFarma() {
    return farmacy.getMedicamente();
}

void Service::addMedicamentFarma(const std::string &denumire, const std::string &producator,
                                 const std::string &substActiva, int pret) {
    if (farmacy.findMedicament(denumire)) {
        throw ServiceError("There already exist a medicament with this denumire.");
    }

    Medicament new_medicament(denumire, producator, substActiva, pret);
    Validator::validateMedicament(new_medicament);

    farmacy.addMedicament(new_medicament);
    history.push_back(std::make_unique<UndoAdd>(farmacy, new_medicament));
}

void Service::updateMedicamentFarma(const std::string &denumire, const std::string &new_producator,
                                    const std::string &new_substActiva, int new_pret) {
    if (!farmacy.findMedicament(denumire)) {
        throw ServiceError("There are no medicamente with this denumire.");
    }

    Medicament new_medicament(denumire, new_producator, new_substActiva, new_pret);
    Validator::validateMedicament(new_medicament);

    auto updated_medicament = farmacy.updateMedicament(denumire, new_medicament);
    history.push_back(std::make_unique<UndoUpdate>(farmacy, updated_medicament));
}

void Service::deleteMedicamentFarma(const std::string &denumire) {
    if (!farmacy.findMedicament(denumire)) {
        throw ServiceError("There are no medicamente with this denumire.");
    }

    auto deleted_medicament = farmacy.deleteMedicament(denumire);
    history.push_back(std::make_unique<UndoDelete>(farmacy, deleted_medicament));
}

std::vector<Medicament> Service::findMedicamentFarma(const std::string &denumire) {
    std::vector<Medicament> found_medicamente;
    std::vector<Medicament> all_medicamente = farmacy.getMedicamente();

    std::copy_if(all_medicamente.begin(), all_medicamente.end(), std::back_inserter(found_medicamente),
                 [&denumire](const Medicament &medicament) { return medicament.getDenumire().find(denumire) == 0; });

    return found_medicamente;
}

std::vector<Medicament> Service::filterProducator(const std::string &producator) {
    std::vector<Medicament> filtered_medicamente;
    std::vector<Medicament> all_medicamente = farmacy.getMedicamente();

    std::copy_if(all_medicamente.begin(),
                 all_medicamente.end(),
                 std::back_inserter(filtered_medicamente),
                 [&producator](const Medicament &medicament) { return medicament.getProducator() == producator; });

    return filtered_medicamente;
}

std::vector<Medicament> Service::filterMedicamenteFarma(int min_pret) {
    std::vector<Medicament> filtered_medicamente;
    std::vector<Medicament> all_medicamente = farmacy.getMedicamente();

    std::copy_if(all_medicamente.begin(),
                 all_medicamente.end(),
                 std::back_inserter(filtered_medicamente),
                 [min_pret](const Medicament &medicament) { return medicament.getPret() >= min_pret; });

    return filtered_medicamente;
}

std::vector<Medicament> Service::sortMedicamenteFarma(
        const std::function<bool(const Medicament &, const Medicament &)> &compare) {
    std::vector<Medicament> sorted_medicamente = farmacy.getMedicamente();
    std::sort(sorted_medicamente.begin(), sorted_medicamente.end(), compare);

    return sorted_medicamente;
}

/*
 * RECIPE
 */

std::vector<Medicament> &Service::getAllRecipe() {
    return recipe.getMedicamente();
}

void Service::addMedicamentRecipe(const std::string &denumire) {
    if (!farmacy.findMedicament(denumire)) {
        throw ServiceError("There is not medicament with this denumire to add in the recipe.");
    }

    auto medicamente = farmacy.getMedicamente();

    auto it = std::find_if(medicamente.begin(), medicamente.end(),
                           [&denumire](const Medicament &medicament) {
                               return medicament.getDenumire() == denumire;
                           });

    recipe.addMedicament(*it);
    notify();
}

void Service::deleteAllMedicamentsRecipe() {
    if (recipe.getLen() == 0) {
        throw ServiceError("There are already no medicamente in the recipe.");
    }

    recipe.deleteAllMedicamente();
    notify();
}

void Service::populateRandomRecipe(size_t medicament_count) {
    if (farmacy.getLen() == 0) {
        throw ServiceError("There are no medicamente in the farmacy");
    }

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(farmacy.getLen() - 1));

    for (size_t i = 0; i < medicament_count; ++i) {
        int random_number = distribution(gen);
        recipe.addMedicament(farmacy.getMedicamente()[random_number]);
    }
    notify();
}

void Service::exportHTML(const std::string &filename) {
    std::ofstream output_file(filename);

    output_file << "<!DOCTYPE html>\n<html lang=\"en\">\n"
                << "<head>\n<title>Medicament List</title>\n"
                << "<link rel=\"stylesheet\" href=\"style.css\">\n"
                << "\n</head>\n<body>\n";
    output_file << "<h1>Medicament List</h1>\n<ul>\n";

    for (const auto &medicament : getAllRecipe()) {
        output_file << "<li>\n";
        output_file << "<strong>Denumire:</strong> " << medicament.getDenumire() << "<br>\n";
        output_file << "<strong>Producator:</strong> " << medicament.getProducator() << "<br>\n";
        output_file << "<strong>SubstActiva:</strong> " << medicament.getSubstActiva() << "<br>\n";
        output_file << "<strong>Pret:</strong> " << medicament.getPret() << "<br>\n";
        output_file << "</li>\n";
    }

    output_file << "</ul>\n</body>\n</html>\n";
}

void Service::exportCSV(const std::string &filename) {
    std::ofstream output_file(filename);

    output_file << "Denumire,Producator,SubstActiva,Pret\n";

    for (const auto &medicament : getAllRecipe()) {
        output_file << "\"" << medicament.getDenumire() << "\",";
        output_file << "\"" << medicament.getProducator() << "\",";
        output_file << "\"" << medicament.getSubstActiva() << "\",";
        output_file << "\"" << medicament.getPret() << "\"\n";
    }

    output_file.close();
}

/*
 * Undo and Raport
 */

std::unordered_map<std::string, int> Service::getProducatorReport() {
    std::unordered_map<std::string, int> raport;

    for (const Medicament &medicament : farmacy.getMedicamente()) {
        raport[medicament.getProducator()] += 1;
    }

    return raport;
}

void Service::undo() {
    if (history.empty()) {
        throw ServiceError{"You can't undo any further."};
    }

    auto last_action = std::move(history.back());
    history.pop_back();

    last_action->doUndo();
}