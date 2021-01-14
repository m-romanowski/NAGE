import com.structurizr.Workspace;
import com.structurizr.view.PaperSize;
import com.structurizr.view.StaticView;
import com.structurizr.view.ViewSet;

import java.util.function.Function;

class ViewCreator {
    static Workspace setupView(Workspace workspace, Function<ViewSet, StaticView> viewGenerator) {
        return setupView(workspace, viewGenerator, PaperSize.A4_Landscape);
    }

    static Workspace setupView(Workspace workspace, Function<ViewSet, StaticView> viewGenerator, PaperSize paperSize) {
        ViewSet views = workspace.getViews();
        StaticView contextView = viewGenerator.apply(views);
        contextView.setPaperSize(paperSize);
        contextView.addAllElements();
        return workspace;
    }
}
