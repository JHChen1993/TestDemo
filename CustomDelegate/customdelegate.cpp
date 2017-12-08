#include "customdelegate.h"
#include <QCheckBox>

TableHeaderView::TableHeaderView(Qt::Orientation orientation, QWidget *parent)
	: QHeaderView(orientation, parent)
	, mCheckCol(0)
	, mPressed(false)
	, mChecked(false)
	, mTristate(false)
	, mNoChange(false)
	, mMoving(false)
{
 	setHighlightSections(true);
	setMouseTracking(true);
	/// <响应鼠标>
 	setSectionsClickable(true);
}

void TableHeaderView::SetCheckCol(quint32 ncol)
{
	mCheckCol = ncol;
}

void TableHeaderView::paintSection(QPainter *painter, const QRect &rect, int index) const
{
	painter->save();
	QHeaderView::paintSection(painter, rect, index);
	painter->restore();

	if (index == mCheckCol) {
		QStyleOptionButton option;

		option.initFrom(this);

		/// <复选框下陷效果>
		if (mChecked) {
			option.state |= QStyle::State_Sunken;
		}
		/// <checked状态>
		option.state |= mChecked ? QStyle::State_On : QStyle::State_Off;

		/// <>
		if (testAttribute(Qt::WA_Hover) && underMouse()) {
			if (mMoving) {
				option.state |= QStyle::State_MouseOver;
			}
			else {
				option.state &= ~QStyle::State_MouseOver;
			}
		}
		
		/// <绘制复选框>
		QCheckBox checkBox;
		option.iconSize = QSize(20, 20);
		option.rect = rect;
		option.rect.adjust(3, 0, 0, 0);
		style()->drawControl(QStyle::CE_CheckBox, &option, painter, this);
	}
}

void TableHeaderView::mousePressEvent(QMouseEvent *event)
{
	int column = logicalIndexAt(event->pos());
	if ((event->buttons() & Qt::LeftButton) && (column == mCheckCol)) {
		mPressed = true;
	}
	else {
		QHeaderView::mousePressEvent(event);
	}
}

void TableHeaderView::mouseReleaseEvent(QMouseEvent *event)
{
	QRect nRect = { 3, 3, 20, 20 };

	if (mPressed) {
		auto ps = event->pos();
		if (nRect.contains(ps)) {
			if (mTristate && mNoChange) {
				mChecked = true;
				mNoChange = false;
			} else {
				mChecked = !mChecked;
			}

			Qt::CheckState state = mChecked ? Qt::Checked : Qt::Unchecked;

			emit Signal_StateChanged(state);
		}
	}
	else {
		QHeaderView::mouseReleaseEvent(event);
	}

	this->viewport()->update();
	mPressed = false;
}

bool TableHeaderView::event(QEvent *event)
{
	if (event->type() == QEvent::Enter || event->type() == QEvent::Leave ||
		event->type() == QEvent::MouseMove) {
		QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);
		int nColumn = logicalIndexAt(pEvent->x());
		if (nColumn == mCheckCol) {
			mMoving = (event->type() == QEvent::Enter);
			this->viewport()->update();
			return true;
		}
	}
	return QHeaderView::event(event);
}

CustomDelegate::CustomDelegate(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	auto hd = new TableHeaderView(Qt::Horizontal, this);
	ui.wdt_tb->setHorizontalHeader(hd);

	QObject::connect(hd, &TableHeaderView::Signal_StateChanged, [this](Qt::CheckState state){
		for (int i = 0; i < ui.wdt_tb->rowCount(); ++i){
			ui.wdt_tb->item(i, 0)->setCheckState(state);
		}
	});
}

CustomDelegate::~CustomDelegate()
{

}
