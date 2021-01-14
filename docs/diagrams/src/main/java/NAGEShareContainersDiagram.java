import com.structurizr.Workspace;
import com.structurizr.model.Container;
import com.structurizr.model.InteractionStyle;
import com.structurizr.model.SoftwareSystem;
import com.structurizr.view.StaticView;
import com.structurizr.view.ViewSet;
import lombok.Getter;
import lombok.experimental.FieldDefaults;

import java.util.function.Function;

import static lombok.AccessLevel.PRIVATE;

class NAGEShareContainersDiagram {
    static InternalContainers create(Workspace workspace, SoftwareSystem nageShareSystem, ExternalSystems externalSystems) {
        InternalContainers internalContainers = new InternalContainers(nageShareSystem);
        internalContainers.createUsages(externalSystems);
        setupContainerView(workspace, nageShareSystem);
        return internalContainers;
    }

    private static void setupContainerView(Workspace workspace, SoftwareSystem eMobility) {
        Function<ViewSet, StaticView> containerViewCreator = views ->
            views.createContainerView(
                eMobility,
                "NAGE share containers",
                "NAGE share container view");
        ViewCreator.setupView(workspace, containerViewCreator);
    }
}

@Getter
@FieldDefaults(makeFinal = true, level = PRIVATE)
class InternalContainers {

    Container bigMonilithicApplication;

    InternalContainers(SoftwareSystem eMobility) {
        bigMonilithicApplication = eMobility.addContainer("NAGE", "Game engine", "C++");
    }

    void createUsages(ExternalSystems externalSystems) {
        externalSystems.getNageEditor().uses(bigMonilithicApplication, "graphical interactions", DataBus.EVENTBUS, InteractionStyle.Synchronous);
    }
}
