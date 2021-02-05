#include "materialwidget.h"

namespace mr::qnage
{
    MaterialWidget::MaterialWidget(QWidget* _parent)
        : QWidget(_parent)
    {
        setupUi();
    }

    MaterialWidget::~MaterialWidget()
    {
        delete widgetHeaderBar_;
        delete texturePicker_;
        delete mainLayout_;
    }

    void MaterialWidget::setupUi()
    {
        this->mainLayout_ = new QVBoxLayout;
        this->setLayout(this->mainLayout_);

        this->widgetHeaderBar_ = new HeaderBar("Material");
        this->mainLayout_->addWidget(this->widgetHeaderBar_);

        this->texturePicker_ = new TexturePicker(this);
        this->mainLayout_->addWidget(this->texturePicker_);
    }
}
