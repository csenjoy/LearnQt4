## 使用ui文件，调用setupUi后 layout为空问题
  in SortDialog.cc line 56-58

## 没有收到QPushButton toggled signal问题
  QPushButton需要设置checkable属性为true

## QLayout::setSizeConstraint(QLayout::SetFixedSize)
  布局内容不会随着布局大小改变; 