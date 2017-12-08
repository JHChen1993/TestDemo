#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include "ui_customdelegate.h"

/// <带复选框的TABLE-HEADER>
class TableHeaderView
	: public QHeaderView
{
	Q_OBJECT

public:
	TableHeaderView(Qt::Orientation orientation, QWidget *parent = 0);

public:
	/// <设置某行checked>
	void SetCheckCol(quint32 ncol);

protected:
	/// <绘制复选框>
	virtual void paintSection(QPainter *painter, const QRect &rect, int index) const;

	/// <鼠标按下表头>
	virtual void mousePressEvent(QMouseEvent *event);

	/// <鼠标从表头释放，发送信号，更新model数据>
	virtual void mouseReleaseEvent(QMouseEvent *event);

	/// <鼠标滑过、离开，更新复选框状态>
	virtual bool event(QEvent *event);

signals:
	void Signal_StateChanged(Qt::CheckState);

private:
	bool mPressed;
	bool mChecked;
	bool mTristate;
	bool mNoChange;
	bool mMoving;
	quint32 mCheckCol;
};


class CustomDelegate : public QMainWindow
{
	Q_OBJECT

public:
	CustomDelegate(QWidget *parent = 0);
	~CustomDelegate();

private:
	Ui::CustomDelegateClass ui;
};

#endif // CUSTOMDELEGATE_H
