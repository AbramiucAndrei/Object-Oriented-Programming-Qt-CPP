#include "Undo.hpp"

UndoAdd::UndoAdd(AbstractFarmacy &farmacy, Medicament medicament) : medicament{std::move(medicament)}, farmacy{farmacy} {}

void UndoAdd::doUndo() {
    farmacy.deleteMedicament(medicament.getDenumire());
}

UndoDelete::UndoDelete(AbstractFarmacy &farmacy, Medicament medicament) : medicament{std::move(medicament)}, farmacy{farmacy} {}

void UndoDelete::doUndo() {
    farmacy.addMedicament(medicament);
}

UndoUpdate::UndoUpdate(AbstractFarmacy &farmacy, Medicament medicament) : medicament{std::move(medicament)}, farmacy{farmacy} {}

void UndoUpdate::doUndo() {
    farmacy.updateMedicament(medicament.getDenumire(), medicament);
}