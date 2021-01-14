import com.structurizr.Workspace;
import com.structurizr.model.Component;
import com.structurizr.model.Container;
import com.structurizr.model.InteractionStyle;
import com.structurizr.view.PaperSize;
import com.structurizr.view.StaticView;
import com.structurizr.view.ViewSet;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.experimental.FieldDefaults;

import java.util.function.Function;

public class NAGEShareComponents {

    static SampleNAGEShareModules create(Workspace workspace, InternalContainers internalContainers, ExternalSystems externalSystems) {
        SampleNAGEShareModules sampleNAGEShareModules = new SampleNAGEShareModules(internalContainers.getBigMonilithicApplication());
        sampleNAGEShareModules.createUsages(internalContainers, externalSystems);
        setupComponentView(workspace, internalContainers.getBigMonilithicApplication());
        return sampleNAGEShareModules;
    }

    private static void setupComponentView(Workspace workspace, Container oldBackend) {
        Function<ViewSet, StaticView> componentViewCreator = views ->
            views.createComponentView(oldBackend,
                "NAGE sharing monolith components",
                "NAGE sharing monolith components");
        ViewCreator.setupView(workspace, componentViewCreator, PaperSize.A2_Landscape);
    }
}

@Getter
@FieldDefaults(makeFinal = true, level = AccessLevel.PRIVATE)
class SampleNAGEShareModules {

    ExternalSystemsInteractor externalSystemsInteractor = new ExternalSystemsInteractor();
    InternalModulesInteractor internalModulesInteractor = new InternalModulesInteractor();
    Component coreEngine, renderEngine, sceneManager, io, igame;

    SampleNAGEShareModules(Container nageSharing) {
        coreEngine = nageSharing.addComponent("Core Engine", "Core of the engine, main event loop");
        renderEngine = nageSharing.addComponent("Render Engine", "Manages render processes");
        sceneManager = nageSharing.addComponent("Scene manager", "Manages every scenes");
        io = nageSharing.addComponent("IO", "Window, keyboard and mouse events");
        igame = nageSharing.addComponent("IGame", "New game interface");
    }

    void createUsages(InternalContainers internalContainers, ExternalSystems externalSystems) {
        externalSystemsInteractor.createCallsFromExternalSystems(internalContainers, externalSystems);
        internalModulesInteractor.createCallsFromInternalModules(internalContainers.getBigMonilithicApplication());
    }

    private class InternalModulesInteractor {

        private void createCallsFromInternalModules(Container bigApp) {
            coreEngine.uses(io, "Poll the next events", DataBus.EVENTBUS, InteractionStyle.Synchronous);
            coreEngine.uses(igame, "Inject game io events", DataBus.EVENTBUS, InteractionStyle.Synchronous);
            coreEngine.uses(renderEngine, "Render next frame", DataBus.CALL_METHOD, InteractionStyle.Synchronous);
            renderEngine.uses(sceneManager, "Get all renderable scene objects", DataBus.CALL_METHOD, InteractionStyle.Synchronous);
            renderEngine.uses(io, "Refresh window render area", DataBus.CALL_METHOD, InteractionStyle.Synchronous);
        }
    }

    private class ExternalSystemsInteractor {
        private void createCallsFromExternalSystems(InternalContainers internalContainers, ExternalSystems externalSystems) {
            externalSystems.getNageEditor().uses(io, "register new IO call", DataBus.EVENTBUS,
                InteractionStyle.Synchronous);
            externalSystems.getNageEditor().uses(sceneManager, "register new scene object transformation", DataBus.EVENTBUS,
                InteractionStyle.Synchronous);
        }
    }
}
