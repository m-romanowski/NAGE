import com.structurizr.Workspace;
import com.structurizr.model.Model;
import com.structurizr.model.SoftwareSystem;
import com.structurizr.view.PaperSize;
import com.structurizr.view.StaticView;
import com.structurizr.view.ViewSet;
import lombok.Getter;
import lombok.experimental.FieldDefaults;

import java.util.function.Function;

import static lombok.AccessLevel.PRIVATE;

class NAGEShareContextDiagram {
    static ExternalSystems create(Workspace workspace, Model model, SoftwareSystem nageShare) {
        ExternalSystems externalSystems = new ExternalSystems(model);
        externalSystems.createUsages(nageShare);
        setupContextView(workspace, nageShare);
        return externalSystems;
    }

    private static void setupContextView(Workspace workspace, SoftwareSystem eMobility) {
        Function<ViewSet, StaticView> contextViewCrator = views ->
            views.createSystemContextView(
                eMobility,
                "NAGE context diagram",
                "NAGE context view");
        ViewCreator.setupView(workspace, contextViewCrator, PaperSize.A5_Landscape);
    }
}

@Getter
@FieldDefaults(makeFinal = true, level = PRIVATE)
class ExternalSystems {

    SoftwareSystem nageEditor;

    ExternalSystems(Model model) {
        nageEditor = model.addSoftwareSystem("NAGE editor", "Engine graphical editor");
    }

    SoftwareSystem createUsages(SoftwareSystem nageShare) {
        return nageShare;
    }
}
