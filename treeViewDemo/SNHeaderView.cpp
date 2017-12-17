#include "SNHeaderView.h"

SNHeaderView::SNHeaderView(QWidget *parent)
	: QHeaderView(Qt::Horizontal, parent)
{
	m_state = Qt::Unchecked;
	m_bpressed = false;

	setSectionsClickable(true);
}

SNHeaderView::~SNHeaderView()
{

}

void SNHeaderView::paintSection(QPainter *p_painter, const QRect &p_rect, int p_nIndex) const
{
	p_painter->save();
	QHeaderView::paintSection(p_painter, p_rect, p_nIndex);//绘制其他Section
	p_painter->restore();

	//绘制背景色
	p_painter->save();
	p_painter->setBrush(QBrush(Qt::gray));
	p_painter->setPen(Qt::NoPen);
	p_painter->drawRect(p_rect);

	//绘制Section的Text
	p_painter->setFont(QFont("SimSun", 12));
	p_painter->setPen(QColor("#000000"));
	p_painter->drawText(p_rect, Qt::AlignCenter, model()->headerData(p_nIndex, Qt::Horizontal).toString());
	p_painter->restore();

	//为第一列绘制Checkbox
	if (p_nIndex == 0)
	{
		QStyleOptionButton option;
		option.initFrom(this);
		if (m_state == Qt::Unchecked)
		{
			option.state |= QStyle::State_Off;
		}
		else if (m_state == Qt::PartiallyChecked)
		{
			option.state |= QStyle::State_NoChange;
		}
		else if (m_state == Qt::Checked)
		{
			option.state |= QStyle::State_On;
		}
		option.iconSize = QSize(20, 20);
		option.rect = QRect(QPoint(p_rect.left() + 5, p_rect.top() + (p_rect.height() - 20) / 2), QPoint(p_rect.left() + 25, p_rect.bottom() - (p_rect.height() - 20) / 2));
		style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, p_painter);
	}
}

void SNHeaderView::mousePressEvent(QMouseEvent *e)
{
	int nColumn = logicalIndexAt(e->pos());
	if ((e->buttons() & Qt::LeftButton) && (0 == nColumn))
	{
		m_bpressed = true;
		e->accept();
	}
	else
	{
		e->ignore();
	}
}

void SNHeaderView::mouseReleaseEvent(QMouseEvent *e)
{
	if (m_bpressed)
	{
		if (Qt::Unchecked == m_state)
		{
			m_state = Qt::Checked;
		}
		else
		{
			m_state = Qt::Unchecked;
		}

		updateSection(0);
		emit stateChanged(m_state); //状态改变
	}

	m_bpressed = false;
	e->accept();
}

//根据Item的复选框状态，表头复选框状态更新
void SNHeaderView::slot_stateChanged(Qt::CheckState p_state)
{
	m_state = p_state;
	updateSection(0);
}