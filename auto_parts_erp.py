"""
نظام قاصد كريم لقطع غيار السيارات
Qased Kareem Auto Parts ERP System

Professional Desktop ERP with Arabic RTL support
Author: Auto Parts Management Team
"""

import sys
import os
from datetime import datetime, date
from typing import Optional, List
import json
import uuid
import sqlite3

from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QLabel, QLineEdit, QTextEdit, QTableWidget, QTableWidgetItem,
    QComboBox, QSpinBox, QDoubleSpinBox, QDateEdit, QTabWidget, QMessageBox,
    QFileDialog, QDialog, QFormLayout, QListWidget, QScrollArea, QFrame,
    QSplitter, QGroupBox, QCheckBox, QDialogButtonBox
)
from PyQt6.QtCore import Qt, QDate, QSize
from PyQt6.QtGui import QFont, QPixmap, QIcon, QColor, QPalette

try:
    from arabic_reshaper import reshape
    from bidi.algorithm import get_display
    ARABIC_SUPPORT = True
except ImportError:
    ARABIC_SUPPORT = False
    print("Warning: Arabic support libraries not installed")

from database import Database

# Branding colors
COLOR_RED = "#DC143C"
COLOR_BLACK = "#000000"
COLOR_WHITE = "#FFFFFF"
COLOR_LIGHT_GRAY = "#F5F5F5"
COLOR_DARK_GRAY = "#333333"

def format_arabic(text: str) -> str:
    """Format Arabic text for RTL display"""
    if ARABIC_SUPPORT and text:
        reshaped = reshape(text)
        return get_display(reshaped)
    return text

class MainWindow(QMainWindow):
    """Main application window"""
    
    def __init__(self):
        super().__init__()
        self.db = Database()
        self.init_ui()
    
    def init_ui(self):
        """Initialize the user interface"""
        self.setWindowTitle(format_arabic("نظام قاصد كريم لقطع غيار السيارات"))
        self.setMinimumSize(1200, 800)
        
        # Set RTL layout
        self.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        
        # Apply stylesheet
        self.setStyleSheet(f"""
            QMainWindow {{
                background-color: {COLOR_LIGHT_GRAY};
            }}
            QPushButton {{
                background-color: {COLOR_RED};
                color: {COLOR_WHITE};
                border: none;
                padding: 10px 20px;
                font-size: 14pt;
                font-weight: bold;
                border-radius: 5px;
            }}
            QPushButton:hover {{
                background-color: #B91028;
            }}
            QLabel {{
                font-size: 12pt;
                color: {COLOR_BLACK};
            }}
            QLineEdit, QTextEdit, QSpinBox, QDoubleSpinBox, QComboBox {{
                font-size: 12pt;
                padding: 5px;
                border: 2px solid {COLOR_DARK_GRAY};
                border-radius: 3px;
            }}
            QTableWidget {{
                font-size: 11pt;
                gridline-color: {COLOR_DARK_GRAY};
            }}
            QTabWidget::pane {{
                border: 2px solid {COLOR_DARK_GRAY};
            }}
            QTabBar::tab {{
                background-color: {COLOR_WHITE};
                padding: 10px 20px;
                font-size: 12pt;
                font-weight: bold;
            }}
            QTabBar::tab:selected {{
                background-color: {COLOR_RED};
                color: {COLOR_WHITE};
            }}
        """)
        
        # Create central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        # Main layout
        main_layout = QVBoxLayout(central_widget)
        
        # Header
        header = self.create_header()
        main_layout.addWidget(header)
        
        # Tab widget for modules
        self.tabs = QTabWidget()
        self.tabs.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        
        # Add tabs for each module
        self.dashboard_tab = DashboardWidget(self.db)
        self.tabs.addTab(self.dashboard_tab, format_arabic("لوحة التحكم"))
        
        self.inventory_tab = InventoryWidget(self.db)
        self.tabs.addTab(self.inventory_tab, format_arabic("المخزن والصور"))
        
        self.sales_tab = SalesWidget(self.db, self.refresh_dashboard)
        self.tabs.addTab(self.sales_tab, format_arabic("المبيعات"))
        
        self.expenses_tab = ExpensesWidget(self.db, self.refresh_dashboard)
        self.tabs.addTab(self.expenses_tab, format_arabic("المصاريف اليومية"))
        
        self.suppliers_tab = SuppliersWidget(self.db)
        self.tabs.addTab(self.suppliers_tab, format_arabic("حسابات الموردين"))
        
        self.barcode_tab = BarcodeWidget(self.db)
        self.tabs.addTab(self.barcode_tab, format_arabic("الباركود"))
        
        self.alternatives_tab = AlternativesWidget(self.db)
        self.tabs.addTab(self.alternatives_tab, format_arabic("بدائل القطع"))
        
        self.restore_tab = RestoreWidget(self.db)
        self.tabs.addTab(self.restore_tab, format_arabic("استعادة البيانات"))
        
        main_layout.addWidget(self.tabs)
        
        # Connect tab change to refresh
        self.tabs.currentChanged.connect(self.on_tab_changed)
    
    def create_header(self) -> QWidget:
        """Create header with branding"""
        header = QFrame()
        header.setStyleSheet(f"""
            QFrame {{
                background-color: {COLOR_BLACK};
                padding: 20px;
            }}
            QLabel {{
                color: {COLOR_WHITE};
                font-size: 24pt;
                font-weight: bold;
            }}
        """)
        
        layout = QHBoxLayout(header)
        
        title = QLabel(format_arabic("نظام قاصد كريم لقطع غيار السيارات"))
        title.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(title)
        
        return header
    
    def on_tab_changed(self, index: int):
        """Handle tab change event"""
        # Refresh the current tab
        current_widget = self.tabs.widget(index)
        if hasattr(current_widget, 'refresh'):
            current_widget.refresh()
    
    def refresh_dashboard(self):
        """Refresh dashboard statistics"""
        self.dashboard_tab.refresh()
    
    def closeEvent(self, event):
        """Handle application close"""
        self.db.close()
        event.accept()

class DashboardWidget(QWidget):
    """Dashboard with KPIs"""
    
    def __init__(self, db: Database):
        super().__init__()
        self.db = db
        self.init_ui()
        self.refresh()
    
    def init_ui(self):
        """Initialize dashboard UI"""
        layout = QVBoxLayout(self)
        layout.setSpacing(20)
        
        # Title
        title = QLabel(format_arabic("لوحة التحكم - مؤشرات الأداء"))
        title.setStyleSheet(f"font-size: 18pt; font-weight: bold; color: {COLOR_RED};")
        title.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(title)
        
        # KPI cards container
        cards_layout = QHBoxLayout()
        cards_layout.setSpacing(15)
        
        # Total Sales Card
        self.sales_card = self.create_kpi_card(
            format_arabic("إجمالي المبيعات"),
            "0.00",
            COLOR_RED
        )
        cards_layout.addWidget(self.sales_card)
        
        # Net Profit Card
        self.profit_card = self.create_kpi_card(
            format_arabic("صافي الربح"),
            "0.00",
            "#28A745"
        )
        cards_layout.addWidget(self.profit_card)
        
        # Total Expenses Card
        self.expenses_card = self.create_kpi_card(
            format_arabic("إجمالي المصروفات"),
            "0.00",
            "#FFC107"
        )
        cards_layout.addWidget(self.expenses_card)
        
        layout.addLayout(cards_layout)
        
        # Additional stats
        stats_layout = QHBoxLayout()
        
        # Parts count
        self.parts_card = self.create_kpi_card(
            format_arabic("عدد الأصناف"),
            "0",
            "#17A2B8"
        )
        stats_layout.addWidget(self.parts_card)
        
        # Low stock warning
        self.low_stock_card = self.create_kpi_card(
            format_arabic("تحذير مخزون منخفض"),
            "0",
            "#DC3545"
        )
        stats_layout.addWidget(self.low_stock_card)
        
        layout.addLayout(stats_layout)
        
        layout.addStretch()
    
    def create_kpi_card(self, title: str, value: str, color: str) -> QFrame:
        """Create a KPI card"""
        card = QFrame()
        card.setStyleSheet(f"""
            QFrame {{
                background-color: {COLOR_WHITE};
                border: 3px solid {color};
                border-radius: 10px;
                padding: 20px;
            }}
        """)
        
        card_layout = QVBoxLayout(card)
        
        title_label = QLabel(title)
        title_label.setStyleSheet(f"font-size: 14pt; font-weight: bold; color: {color};")
        title_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        card_layout.addWidget(title_label)
        
        value_label = QLabel(value)
        value_label.setObjectName("value")
        value_label.setStyleSheet(f"font-size: 28pt; font-weight: bold; color: {color};")
        value_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        card_layout.addWidget(value_label)
        
        return card
    
    def refresh(self):
        """Refresh dashboard statistics"""
        stats = self.db.get_dashboard_stats()
        
        # Update sales
        sales_label = self.sales_card.findChild(QLabel, "value")
        if sales_label:
            sales_label.setText(f"{stats['total_sales']:.2f}")
        
        # Update profit
        profit_label = self.profit_card.findChild(QLabel, "value")
        if profit_label:
            profit_label.setText(f"{stats['net_profit']:.2f}")
        
        # Update expenses
        expenses_label = self.expenses_card.findChild(QLabel, "value")
        if expenses_label:
            expenses_label.setText(f"{stats['total_expenses']:.2f}")
        
        # Update parts count
        parts_label = self.parts_card.findChild(QLabel, "value")
        if parts_label:
            parts_label.setText(str(stats['parts_count']))
        
        # Update low stock
        low_stock_label = self.low_stock_card.findChild(QLabel, "value")
        if low_stock_label:
            low_stock_label.setText(str(stats['low_stock_count']))


class InventoryWidget(QWidget):
    """Inventory management with image support"""
    
    def __init__(self, db: Database):
        super().__init__()
        self.db = db
        self.current_image_path = None
        self.init_ui()
        self.refresh()
    
    def init_ui(self):
        """Initialize inventory UI"""
        layout = QVBoxLayout(self)
        
        # Title
        title = QLabel(format_arabic("إدارة المخزن والصور"))
        title.setStyleSheet(f"font-size: 16pt; font-weight: bold; color: {COLOR_RED};")
        layout.addWidget(title)
        
        # Form for adding/editing parts
        form_group = QGroupBox(format_arabic("إضافة/تعديل قطعة"))
        form_layout = QFormLayout()
        
        self.part_name_input = QLineEdit()
        form_layout.addRow(format_arabic("اسم القطعة:"), self.part_name_input)
        
        self.brand_input = QLineEdit()
        form_layout.addRow(format_arabic("الماركة:"), self.brand_input)
        
        self.price_input = QDoubleSpinBox()
        self.price_input.setMaximum(999999.99)
        self.price_input.setSuffix(" " + format_arabic("جنيه"))
        form_layout.addRow(format_arabic("السعر:"), self.price_input)
        
        self.cost_input = QDoubleSpinBox()
        self.cost_input.setMaximum(999999.99)
        self.cost_input.setSuffix(" " + format_arabic("جنيه"))
        form_layout.addRow(format_arabic("التكلفة:"), self.cost_input)
        
        self.quantity_input = QSpinBox()
        self.quantity_input.setMaximum(999999)
        form_layout.addRow(format_arabic("الكمية:"), self.quantity_input)
        
        # Car brand dropdown
        self.car_brand_combo = QComboBox()
        self.car_brand_combo.setEditable(True)
        self.load_car_brands()
        form_layout.addRow(format_arabic("ماركة السيارة:"), self.car_brand_combo)
        
        # Car model
        self.car_model_input = QLineEdit()
        form_layout.addRow(format_arabic("موديل السيارة:"), self.car_model_input)
        
        # Years
        self.years_input = QLineEdit()
        self.years_input.setPlaceholderText(format_arabic("مثال: 2020-2025"))
        form_layout.addRow(format_arabic("السنوات:"), self.years_input)
        
        # Image upload button
        image_layout = QHBoxLayout()
        self.image_button = QPushButton(format_arabic("اختيار صورة"))
        self.image_button.clicked.connect(self.select_image)
        image_layout.addWidget(self.image_button)
        
        self.image_label = QLabel(format_arabic("لم يتم اختيار صورة"))
        image_layout.addWidget(self.image_label)
        form_layout.addRow(format_arabic("الصورة:"), image_layout)
        
        # Add button
        self.add_button = QPushButton(format_arabic("إضافة قطعة"))
        self.add_button.clicked.connect(self.add_part)
        form_layout.addRow("", self.add_button)
        
        form_group.setLayout(form_layout)
        layout.addWidget(form_group)
        
        # Parts table
        self.parts_table = QTableWidget()
        self.parts_table.setColumnCount(8)
        self.parts_table.setHorizontalHeaderLabels([
            format_arabic("الكود"),
            format_arabic("اسم القطعة"),
            format_arabic("الماركة"),
            format_arabic("السعر"),
            format_arabic("التكلفة"),
            format_arabic("الكمية"),
            format_arabic("السيارة"),
            format_arabic("إجراءات")
        ])
        self.parts_table.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        layout.addWidget(self.parts_table)
    
    def load_car_brands(self):
        """Load car brands for dropdown"""
        brands = [
            "تويوتا", "نيسان", "هوندا", "مازدا", "سوزوكي", "ميتسوبيشي",
            "مرسيدس", "بي ام دبليو", "أودي", "فولكس واجن", "فورد",
            "شيفروليه", "جي ام سي", "دودج", "كيا", "هيونداي",
            "رينو", "بيجو", "سيتروين", "فيات", "أوبل", "سكودا"
        ]
        self.car_brand_combo.addItems([format_arabic(b) for b in brands])
    
    def select_image(self):
        """Select image for part"""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            format_arabic("اختر صورة القطعة"),
            "",
            "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
        )
        if file_path:
            self.current_image_path = file_path
            self.image_label.setText(os.path.basename(file_path))
    
    def add_part(self):
        """Add new part to inventory"""
        part_name = self.part_name_input.text().strip()
        brand = self.brand_input.text().strip()
        price = self.price_input.value()
        cost = self.cost_input.value()
        quantity = self.quantity_input.value()
        car_brand = self.car_brand_combo.currentText()
        car_model = self.car_model_input.text().strip()
        years = self.years_input.text().strip()
        
        if not part_name or not brand:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic("يرجى ملء جميع الحقول المطلوبة"))
            return
        
        # Generate barcode
        barcode = f"QK{uuid.uuid4().hex[:8].upper()}"
        
        # Copy image to images folder if provided
        image_path = ""
        if self.current_image_path:
            images_dir = "part_images"
            os.makedirs(images_dir, exist_ok=True)
            ext = os.path.splitext(self.current_image_path)[1]
            image_filename = f"{barcode}{ext}"
            image_path = os.path.join(images_dir, image_filename)
            try:
                import shutil
                shutil.copy2(self.current_image_path, image_path)
            except Exception as e:
                print(f"Error copying image: {e}")
        
        # Insert into database
        query = """
            INSERT INTO parts (part_name, brand, price, cost, quantity, 
                             car_brand, car_model, years, barcode, image_path)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        """
        result = self.db.execute_update(query, (
            part_name, brand, price, cost, quantity,
            car_brand, car_model, years, barcode, image_path
        ))
        
        if result > 0:
            QMessageBox.information(self, format_arabic("نجح"), 
                                  format_arabic("تمت إضافة القطعة بنجاح"))
            self.clear_form()
            self.refresh()
        else:
            QMessageBox.critical(self, format_arabic("خطأ"), 
                               format_arabic("فشل في إضافة القطعة"))
    
    def clear_form(self):
        """Clear input form"""
        self.part_name_input.clear()
        self.brand_input.clear()
        self.price_input.setValue(0)
        self.cost_input.setValue(0)
        self.quantity_input.setValue(0)
        self.car_brand_combo.setCurrentIndex(0)
        self.car_model_input.clear()
        self.years_input.clear()
        self.current_image_path = None
        self.image_label.setText(format_arabic("لم يتم اختيار صورة"))
    
    def refresh(self):
        """Refresh parts table"""
        query = """
            SELECT id, part_name, brand, price, cost, quantity, 
                   car_brand, car_model, barcode
            FROM parts
            WHERE is_deleted = 0
            ORDER BY id DESC
        """
        parts = self.db.execute_query(query)
        
        self.parts_table.setRowCount(len(parts))
        for row, part in enumerate(parts):
            for col, value in enumerate(part[:-1]):  # Exclude barcode
                item = QTableWidgetItem(str(value))
                item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
                self.parts_table.setItem(row, col, item)
            
            # Delete button
            delete_btn = QPushButton(format_arabic("حذف"))
            delete_btn.clicked.connect(lambda checked, r=row, p_id=part[0]: self.delete_part(p_id))
            self.parts_table.setCellWidget(row, 7, delete_btn)
    
    def delete_part(self, part_id: int):
        """Soft delete a part"""
        reply = QMessageBox.question(
            self,
            format_arabic("تأكيد الحذف"),
            format_arabic("هل أنت متأكد من حذف هذه القطعة؟"),
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if reply == QMessageBox.StandardButton.Yes:
            if self.db.soft_delete("parts", part_id):
                QMessageBox.information(self, format_arabic("نجح"), 
                                      format_arabic("تم حذف القطعة"))
                self.refresh()
            else:
                QMessageBox.critical(self, format_arabic("خطأ"), 
                                   format_arabic("فشل في حذف القطعة"))

class SalesWidget(QWidget):
    """Sales management module"""
    
    def __init__(self, db: Database, refresh_callback):
        super().__init__()
        self.db = db
        self.refresh_callback = refresh_callback
        self.init_ui()
    
    def init_ui(self):
        """Initialize sales UI"""
        layout = QVBoxLayout(self)
        
        # Title
        title = QLabel(format_arabic("إدارة المبيعات"))
        title.setStyleSheet(f"font-size: 16pt; font-weight: bold; color: {COLOR_RED};")
        layout.addWidget(title)
        
        # Form
        form_group = QGroupBox(format_arabic("تسجيل مبيعات"))
        form_layout = QFormLayout()
        
        # Part selection
        self.part_combo = QComboBox()
        self.load_parts()
        form_layout.addRow(format_arabic("القطعة:"), self.part_combo)
        
        # Quantity
        self.sale_quantity = QSpinBox()
        self.sale_quantity.setMinimum(1)
        self.sale_quantity.setMaximum(999)
        form_layout.addRow(format_arabic("الكمية:"), self.sale_quantity)
        
        # Sale date
        self.sale_date = QDateEdit()
        self.sale_date.setDate(QDate.currentDate())
        self.sale_date.setCalendarPopup(True)
        form_layout.addRow(format_arabic("التاريخ:"), self.sale_date)
        
        # Add sale button
        add_sale_btn = QPushButton(format_arabic("تسجيل البيع"))
        add_sale_btn.clicked.connect(self.add_sale)
        form_layout.addRow("", add_sale_btn)
        
        form_group.setLayout(form_layout)
        layout.addWidget(form_group)
        
        # Sales table
        self.sales_table = QTableWidget()
        self.sales_table.setColumnCount(7)
        self.sales_table.setHorizontalHeaderLabels([
            format_arabic("الكود"),
            format_arabic("القطعة"),
            format_arabic("الكمية"),
            format_arabic("السعر"),
            format_arabic("الإجمالي"),
            format_arabic("الربح"),
            format_arabic("التاريخ")
        ])
        self.sales_table.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        layout.addWidget(self.sales_table)
        
        self.refresh()
    
    def load_parts(self):
        """Load available parts"""
        query = "SELECT id, part_name, price FROM parts WHERE is_deleted = 0 AND quantity > 0"
        parts = self.db.execute_query(query)
        
        self.part_combo.clear()
        for part in parts:
            self.part_combo.addItem(f"{part[1]} - {part[2]} جنيه", part[0])
    
    def add_sale(self):
        """Add new sale"""
        if self.part_combo.count() == 0:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic("لا توجد قطع متاحة للبيع"))
            return
        
        part_id = self.part_combo.currentData()
        quantity = self.sale_quantity.value()
        sale_date = self.sale_date.date().toString("yyyy-MM-dd")
        
        # Get part details
        query = "SELECT price, cost, quantity FROM parts WHERE id = ?"
        result = self.db.execute_query(query, (part_id,))
        
        if not result:
            QMessageBox.critical(self, format_arabic("خطأ"), 
                               format_arabic("لم يتم العثور على القطعة"))
            return
        
        price, cost, available_qty = result[0]
        
        if quantity > available_qty:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic(f"الكمية المتاحة فقط {available_qty}"))
            return
        
        total_price = price * quantity
        total_cost = cost * quantity
        profit = total_price - total_cost
        
        # Insert sale
        sale_query = """
            INSERT INTO sales (part_id, quantity, unit_price, unit_cost, 
                             total_price, profit, sale_date)
            VALUES (?, ?, ?, ?, ?, ?, ?)
        """
        result = self.db.execute_update(sale_query, (
            part_id, quantity, price, cost, total_price, profit, sale_date
        ))
        
        if result > 0:
            # Update inventory
            update_query = "UPDATE parts SET quantity = quantity - ? WHERE id = ?"
            self.db.execute_update(update_query, (quantity, part_id))
            
            QMessageBox.information(self, format_arabic("نجح"), 
                                  format_arabic("تم تسجيل البيع بنجاح"))
            self.refresh()
            self.refresh_callback()
        else:
            QMessageBox.critical(self, format_arabic("خطأ"), 
                               format_arabic("فشل في تسجيل البيع"))
    
    def refresh(self):
        """Refresh sales table"""
        query = """
            SELECT s.id, p.part_name, s.quantity, s.unit_price, 
                   s.total_price, s.profit, s.sale_date
            FROM sales s
            JOIN parts p ON s.part_id = p.id
            WHERE s.is_deleted = 0
            ORDER BY s.id DESC
            LIMIT 100
        """
        sales = self.db.execute_query(query)
        
        self.sales_table.setRowCount(len(sales))
        for row, sale in enumerate(sales):
            for col, value in enumerate(sale):
                item = QTableWidgetItem(str(value))
                item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
                self.sales_table.setItem(row, col, item)
        
        self.load_parts()


class ExpensesWidget(QWidget):
    """Daily small expenses module"""
    
    def __init__(self, db: Database, refresh_callback):
        super().__init__()
        self.db = db
        self.refresh_callback = refresh_callback
        self.init_ui()
    
    def init_ui(self):
        """Initialize expenses UI"""
        layout = QVBoxLayout(self)
        
        # Title
        title = QLabel(format_arabic("المصاريف الصغيرة واليومية"))
        title.setStyleSheet(f"font-size: 16pt; font-weight: bold; color: {COLOR_RED};")
        layout.addWidget(title)
        
        # Form
        form_group = QGroupBox(format_arabic("تسجيل مصروف"))
        form_layout = QFormLayout()
        
        # Expense type
        self.expense_type = QComboBox()
        expense_types = ["طعام", "شاي", "تنظيف", "سلف موظفين", "مواصلات", "أخرى"]
        self.expense_type.addItems([format_arabic(t) for t in expense_types])
        form_layout.addRow(format_arabic("نوع المصروف:"), self.expense_type)
        
        # Amount
        self.expense_amount = QDoubleSpinBox()
        self.expense_amount.setMaximum(999999.99)
        self.expense_amount.setSuffix(" " + format_arabic("جنيه"))
        form_layout.addRow(format_arabic("المبلغ:"), self.expense_amount)
        
        # Description
        self.expense_desc = QLineEdit()
        form_layout.addRow(format_arabic("الوصف:"), self.expense_desc)
        
        # Date
        self.expense_date = QDateEdit()
        self.expense_date.setDate(QDate.currentDate())
        self.expense_date.setCalendarPopup(True)
        form_layout.addRow(format_arabic("التاريخ:"), self.expense_date)
        
        # Add button
        add_expense_btn = QPushButton(format_arabic("إضافة مصروف"))
        add_expense_btn.clicked.connect(self.add_expense)
        form_layout.addRow("", add_expense_btn)
        
        form_group.setLayout(form_layout)
        layout.addWidget(form_group)
        
        # Expenses table
        self.expenses_table = QTableWidget()
        self.expenses_table.setColumnCount(6)
        self.expenses_table.setHorizontalHeaderLabels([
            format_arabic("الكود"),
            format_arabic("النوع"),
            format_arabic("المبلغ"),
            format_arabic("الوصف"),
            format_arabic("التاريخ"),
            format_arabic("إجراءات")
        ])
        self.expenses_table.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        layout.addWidget(self.expenses_table)
        
        self.refresh()
    
    def add_expense(self):
        """Add new expense"""
        expense_type = self.expense_type.currentText()
        amount = self.expense_amount.value()
        description = self.expense_desc.text().strip()
        expense_date = self.expense_date.date().toString("yyyy-MM-dd")
        
        if amount <= 0:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic("يرجى إدخال مبلغ صحيح"))
            return
        
        query = """
            INSERT INTO daily_expenses (expense_type, amount, description, expense_date)
            VALUES (?, ?, ?, ?)
        """
        result = self.db.execute_update(query, (expense_type, amount, description, expense_date))
        
        if result > 0:
            QMessageBox.information(self, format_arabic("نجح"), 
                                  format_arabic("تمت إضافة المصروف بنجاح"))
            self.expense_amount.setValue(0)
            self.expense_desc.clear()
            self.refresh()
            self.refresh_callback()
        else:
            QMessageBox.critical(self, format_arabic("خطأ"), 
                               format_arabic("فشل في إضافة المصروف"))
    
    def refresh(self):
        """Refresh expenses table"""
        query = """
            SELECT id, expense_type, amount, description, expense_date
            FROM daily_expenses
            WHERE is_deleted = 0
            ORDER BY id DESC
            LIMIT 100
        """
        expenses = self.db.execute_query(query)
        
        self.expenses_table.setRowCount(len(expenses))
        for row, expense in enumerate(expenses):
            for col, value in enumerate(expense):
                item = QTableWidgetItem(str(value))
                item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
                self.expenses_table.setItem(row, col, item)
            
            # Delete button
            delete_btn = QPushButton(format_arabic("حذف"))
            delete_btn.clicked.connect(lambda checked, e_id=expense[0]: self.delete_expense(e_id))
            self.expenses_table.setCellWidget(row, 5, delete_btn)
    
    def delete_expense(self, expense_id: int):
        """Delete an expense"""
        reply = QMessageBox.question(
            self,
            format_arabic("تأكيد الحذف"),
            format_arabic("هل أنت متأكد من حذف هذا المصروف؟"),
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if reply == QMessageBox.StandardButton.Yes:
            if self.db.soft_delete("daily_expenses", expense_id):
                QMessageBox.information(self, format_arabic("نجح"), 
                                      format_arabic("تم حذف المصروف"))
                self.refresh()
                self.refresh_callback()
            else:
                QMessageBox.critical(self, format_arabic("خطأ"), 
                                   format_arabic("فشل في حذف المصروف"))

class SuppliersWidget(QWidget):
    """Supplier ledger management"""
    
    def __init__(self, db: Database):
        super().__init__()
        self.db = db
        self.init_ui()
    
    def init_ui(self):
        """Initialize suppliers UI"""
        layout = QVBoxLayout(self)
        
        # Title
        title = QLabel(format_arabic("حسابات الموردين"))
        title.setStyleSheet(f"font-size: 16pt; font-weight: bold; color: {COLOR_RED};")
        layout.addWidget(title)
        
        # Splitter for suppliers and transactions
        splitter = QSplitter(Qt.Orientation.Horizontal)
        
        # Left: Suppliers list
        suppliers_widget = QWidget()
        suppliers_layout = QVBoxLayout(suppliers_widget)
        
        # Add supplier form
        add_form = QGroupBox(format_arabic("إضافة مورد"))
        add_layout = QFormLayout()
        
        self.supplier_name = QLineEdit()
        add_layout.addRow(format_arabic("اسم المورد:"), self.supplier_name)
        
        self.supplier_contact = QLineEdit()
        add_layout.addRow(format_arabic("معلومات الاتصال:"), self.supplier_contact)
        
        add_supplier_btn = QPushButton(format_arabic("إضافة مورد"))
        add_supplier_btn.clicked.connect(self.add_supplier)
        add_layout.addRow("", add_supplier_btn)
        
        add_form.setLayout(add_layout)
        suppliers_layout.addWidget(add_form)
        
        # Suppliers table
        self.suppliers_table = QTableWidget()
        self.suppliers_table.setColumnCount(4)
        self.suppliers_table.setHorizontalHeaderLabels([
            format_arabic("الكود"),
            format_arabic("الاسم"),
            format_arabic("الرصيد"),
            format_arabic("إجراءات")
        ])
        self.suppliers_table.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        self.suppliers_table.cellClicked.connect(self.load_transactions)
        suppliers_layout.addWidget(self.suppliers_table)
        
        splitter.addWidget(suppliers_widget)
        
        # Right: Transactions
        transactions_widget = QWidget()
        transactions_layout = QVBoxLayout(transactions_widget)
        
        # Add transaction form
        trans_form = QGroupBox(format_arabic("إضافة معاملة"))
        trans_layout = QFormLayout()
        
        self.trans_type = QComboBox()
        self.trans_type.addItems([format_arabic("شراء"), format_arabic("دفع")])
        trans_layout.addRow(format_arabic("النوع:"), self.trans_type)
        
        self.trans_amount = QDoubleSpinBox()
        self.trans_amount.setMaximum(999999.99)
        self.trans_amount.setSuffix(" " + format_arabic("جنيه"))
        trans_layout.addRow(format_arabic("المبلغ:"), self.trans_amount)
        
        self.trans_desc = QLineEdit()
        trans_layout.addRow(format_arabic("الوصف:"), self.trans_desc)
        
        self.trans_date = QDateEdit()
        self.trans_date.setDate(QDate.currentDate())
        self.trans_date.setCalendarPopup(True)
        trans_layout.addRow(format_arabic("التاريخ:"), self.trans_date)
        
        add_trans_btn = QPushButton(format_arabic("إضافة معاملة"))
        add_trans_btn.clicked.connect(self.add_transaction)
        trans_layout.addRow("", add_trans_btn)
        
        trans_form.setLayout(trans_layout)
        transactions_layout.addWidget(trans_form)
        
        # Transactions table
        self.transactions_table = QTableWidget()
        self.transactions_table.setColumnCount(5)
        self.transactions_table.setHorizontalHeaderLabels([
            format_arabic("الكود"),
            format_arabic("النوع"),
            format_arabic("المبلغ"),
            format_arabic("الوصف"),
            format_arabic("التاريخ")
        ])
        self.transactions_table.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        transactions_layout.addWidget(self.transactions_table)
        
        splitter.addWidget(transactions_widget)
        
        layout.addWidget(splitter)
        
        self.current_supplier_id = None
        self.refresh()
    
    def add_supplier(self):
        """Add new supplier"""
        name = self.supplier_name.text().strip()
        contact = self.supplier_contact.text().strip()
        
        if not name:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic("يرجى إدخال اسم المورد"))
            return
        
        query = "INSERT INTO suppliers (supplier_name, contact_info) VALUES (?, ?)"
        result = self.db.execute_update(query, (name, contact))
        
        if result > 0:
            QMessageBox.information(self, format_arabic("نجح"), 
                                  format_arabic("تمت إضافة المورد بنجاح"))
            self.supplier_name.clear()
            self.supplier_contact.clear()
            self.refresh()
        else:
            QMessageBox.critical(self, format_arabic("خطأ"), 
                               format_arabic("فشل في إضافة المورد"))
    
    def add_transaction(self):
        """Add transaction for current supplier"""
        if self.current_supplier_id is None:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic("يرجى اختيار مورد أولاً"))
            return
        
        trans_type = self.trans_type.currentText()
        amount = self.trans_amount.value()
        description = self.trans_desc.text().strip()
        trans_date = self.trans_date.date().toString("yyyy-MM-dd")
        
        if amount <= 0:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic("يرجى إدخال مبلغ صحيح"))
            return
        
        # Insert transaction
        query = """
            INSERT INTO supplier_transactions 
            (supplier_id, transaction_type, amount, description, transaction_date)
            VALUES (?, ?, ?, ?, ?)
        """
        result = self.db.execute_update(query, (
            self.current_supplier_id, trans_type, amount, description, trans_date
        ))
        
        if result > 0:
            # Update supplier balance
            balance_change = amount if trans_type == format_arabic("شراء") else -amount
            update_query = "UPDATE suppliers SET balance = balance + ? WHERE id = ?"
            self.db.execute_update(update_query, (balance_change, self.current_supplier_id))
            
            QMessageBox.information(self, format_arabic("نجح"), 
                                  format_arabic("تمت إضافة المعاملة بنجاح"))
            self.trans_amount.setValue(0)
            self.trans_desc.clear()
            self.refresh()
            self.load_transactions(self.suppliers_table.currentRow(), 0)
        else:
            QMessageBox.critical(self, format_arabic("خطأ"), 
                               format_arabic("فشل في إضافة المعاملة"))
    
    def refresh(self):
        """Refresh suppliers table"""
        query = """
            SELECT id, supplier_name, balance
            FROM suppliers
            WHERE is_deleted = 0
            ORDER BY id DESC
        """
        suppliers = self.db.execute_query(query)
        
        self.suppliers_table.setRowCount(len(suppliers))
        for row, supplier in enumerate(suppliers):
            for col, value in enumerate(supplier):
                item = QTableWidgetItem(str(value))
                item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
                self.suppliers_table.setItem(row, col, item)
            
            # Delete button
            delete_btn = QPushButton(format_arabic("حذف"))
            delete_btn.clicked.connect(lambda checked, s_id=supplier[0]: self.delete_supplier(s_id))
            self.suppliers_table.setCellWidget(row, 3, delete_btn)
    
    def load_transactions(self, row: int, col: int):
        """Load transactions for selected supplier"""
        supplier_id_item = self.suppliers_table.item(row, 0)
        if supplier_id_item:
            self.current_supplier_id = int(supplier_id_item.text())
            
            query = """
                SELECT id, transaction_type, amount, description, transaction_date
                FROM supplier_transactions
                WHERE supplier_id = ? AND is_deleted = 0
                ORDER BY id DESC
            """
            transactions = self.db.execute_query(query, (self.current_supplier_id,))
            
            self.transactions_table.setRowCount(len(transactions))
            for row, trans in enumerate(transactions):
                for col, value in enumerate(trans):
                    item = QTableWidgetItem(str(value))
                    item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
                    self.transactions_table.setItem(row, col, item)
    
    def delete_supplier(self, supplier_id: int):
        """Delete a supplier"""
        reply = QMessageBox.question(
            self,
            format_arabic("تأكيد الحذف"),
            format_arabic("هل أنت متأكد من حذف هذا المورد؟"),
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if reply == QMessageBox.StandardButton.Yes:
            if self.db.soft_delete("suppliers", supplier_id):
                QMessageBox.information(self, format_arabic("نجح"), 
                                      format_arabic("تم حذف المورد"))
                self.refresh()
            else:
                QMessageBox.critical(self, format_arabic("خطأ"), 
                                   format_arabic("فشل في حذف المورد"))


class BarcodeWidget(QWidget):
    """Barcode generation and printing"""
    
    def __init__(self, db: Database):
        super().__init__()
        self.db = db
        self.init_ui()
    
    def init_ui(self):
        """Initialize barcode UI"""
        layout = QVBoxLayout(self)
        
        # Title
        title = QLabel(format_arabic("إدارة الباركود"))
        title.setStyleSheet(f"font-size: 16pt; font-weight: bold; color: {COLOR_RED};")
        layout.addWidget(title)
        
        # Instructions
        info = QLabel(format_arabic("اختر قطعة لطباعة ملصق الباركود الخاص بها"))
        info.setStyleSheet("font-size: 12pt;")
        layout.addWidget(info)
        
        # Search and filter
        search_layout = QHBoxLayout()
        search_label = QLabel(format_arabic("بحث:"))
        search_layout.addWidget(search_label)
        
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText(format_arabic("ابحث عن قطعة..."))
        self.search_input.textChanged.connect(self.filter_parts)
        search_layout.addWidget(self.search_input)
        
        layout.addLayout(search_layout)
        
        # Parts table with barcodes
        self.parts_table = QTableWidget()
        self.parts_table.setColumnCount(6)
        self.parts_table.setHorizontalHeaderLabels([
            format_arabic("الكود"),
            format_arabic("اسم القطعة"),
            format_arabic("الماركة"),
            format_arabic("الباركود"),
            format_arabic("السعر"),
            format_arabic("إجراءات")
        ])
        self.parts_table.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        layout.addWidget(self.parts_table)
        
        self.refresh()
    
    def refresh(self):
        """Refresh parts table"""
        query = """
            SELECT id, part_name, brand, barcode, price
            FROM parts
            WHERE is_deleted = 0
            ORDER BY id DESC
        """
        parts = self.db.execute_query(query)
        
        self.parts_table.setRowCount(len(parts))
        for row, part in enumerate(parts):
            for col, value in enumerate(part):
                item = QTableWidgetItem(str(value))
                item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
                self.parts_table.setItem(row, col, item)
            
            # Print button
            print_btn = QPushButton(format_arabic("طباعة"))
            print_btn.clicked.connect(lambda checked, p=part: self.print_barcode(p))
            self.parts_table.setCellWidget(row, 5, print_btn)
    
    def filter_parts(self):
        """Filter parts based on search"""
        search_text = self.search_input.text().strip().lower()
        
        for row in range(self.parts_table.rowCount()):
            show_row = False
            for col in range(self.parts_table.columnCount() - 1):
                item = self.parts_table.item(row, col)
                if item and search_text in item.text().lower():
                    show_row = True
                    break
            self.parts_table.setRowHidden(row, not show_row)
    
    def print_barcode(self, part):
        """Generate and print barcode label"""
        part_id, part_name, brand, barcode, price = part
        
        try:
            from reportlab.pdfgen import canvas
            from reportlab.lib.pagesizes import letter
            from reportlab.lib.units import mm
            
            # Create labels directory
            os.makedirs("labels", exist_ok=True)
            
            # Generate PDF label
            filename = f"labels/barcode_{barcode}.pdf"
            c = canvas.Canvas(filename, pagesize=(100*mm, 50*mm))
            
            # Add text
            c.setFont("Helvetica-Bold", 16)
            c.drawString(10*mm, 40*mm, "Qased Kareem")
            
            c.setFont("Helvetica", 12)
            c.drawString(10*mm, 35*mm, f"Part: {part_name[:30]}")
            c.drawString(10*mm, 30*mm, f"Brand: {brand}")
            c.drawString(10*mm, 25*mm, f"Price: {price} EGP")
            
            # Add barcode
            c.setFont("Helvetica-Bold", 14)
            c.drawString(10*mm, 15*mm, f"Code: {barcode}")
            
            # Draw a box for manual barcode
            c.rect(10*mm, 8*mm, 80*mm, 5*mm)
            
            c.save()
            
            QMessageBox.information(
                self,
                format_arabic("نجح"),
                format_arabic(f"تم حفظ الملصق في: {filename}")
            )
            
            # Try to open the PDF
            import subprocess
            import platform
            system = platform.system()
            try:
                if system == "Windows":
                    os.startfile(filename)
                elif system == "Darwin":  # macOS
                    subprocess.run(["open", filename])
                else:  # Linux
                    subprocess.run(["xdg-open", filename])
            except:
                pass
                
        except Exception as e:
            QMessageBox.critical(
                self,
                format_arabic("خطأ"),
                format_arabic(f"فشل في إنشاء الملصق: {str(e)}")
            )

class AlternativesWidget(QWidget):
    """Cross-reference alternatives management"""
    
    def __init__(self, db: Database):
        super().__init__()
        self.db = db
        self.init_ui()
    
    def init_ui(self):
        """Initialize alternatives UI"""
        layout = QVBoxLayout(self)
        
        # Title
        title = QLabel(format_arabic("بدائل القطع"))
        title.setStyleSheet(f"font-size: 16pt; font-weight: bold; color: {COLOR_RED};")
        layout.addWidget(title)
        
        # Add alternative form
        form_group = QGroupBox(format_arabic("ربط قطعة ببديلها"))
        form_layout = QFormLayout()
        
        # Main part
        self.main_part_combo = QComboBox()
        self.load_parts(self.main_part_combo)
        form_layout.addRow(format_arabic("القطعة الأساسية:"), self.main_part_combo)
        
        # Alternative part
        self.alt_part_combo = QComboBox()
        self.load_parts(self.alt_part_combo)
        form_layout.addRow(format_arabic("القطعة البديلة:"), self.alt_part_combo)
        
        # Add button
        add_btn = QPushButton(format_arabic("إضافة بديل"))
        add_btn.clicked.connect(self.add_alternative)
        form_layout.addRow("", add_btn)
        
        form_group.setLayout(form_layout)
        layout.addWidget(form_group)
        
        # Search for alternatives
        search_group = QGroupBox(format_arabic("البحث عن البدائل"))
        search_layout = QVBoxLayout()
        
        search_input_layout = QHBoxLayout()
        self.search_part_combo = QComboBox()
        self.load_parts(self.search_part_combo)
        search_input_layout.addWidget(QLabel(format_arabic("القطعة:")))
        search_input_layout.addWidget(self.search_part_combo)
        
        search_btn = QPushButton(format_arabic("بحث عن البدائل"))
        search_btn.clicked.connect(self.search_alternatives)
        search_input_layout.addWidget(search_btn)
        
        search_layout.addLayout(search_input_layout)
        
        # Results table
        self.results_table = QTableWidget()
        self.results_table.setColumnCount(5)
        self.results_table.setHorizontalHeaderLabels([
            format_arabic("الكود"),
            format_arabic("اسم القطعة البديلة"),
            format_arabic("الماركة"),
            format_arabic("السعر"),
            format_arabic("الكمية المتاحة")
        ])
        self.results_table.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        search_layout.addWidget(self.results_table)
        
        search_group.setLayout(search_layout)
        layout.addWidget(search_group)
        
        # All alternatives table
        self.alternatives_table = QTableWidget()
        self.alternatives_table.setColumnCount(4)
        self.alternatives_table.setHorizontalHeaderLabels([
            format_arabic("القطعة الأساسية"),
            format_arabic("القطعة البديلة"),
            format_arabic("تاريخ الإضافة"),
            format_arabic("إجراءات")
        ])
        self.alternatives_table.setLayoutDirection(Qt.LayoutDirection.RightToLeft)
        layout.addWidget(self.alternatives_table)
        
        self.refresh()
    
    def load_parts(self, combo: QComboBox):
        """Load parts into combo box"""
        query = "SELECT id, part_name, brand FROM parts WHERE is_deleted = 0"
        parts = self.db.execute_query(query)
        
        combo.clear()
        for part in parts:
            combo.addItem(f"{part[1]} - {part[2]}", part[0])
    
    def add_alternative(self):
        """Add alternative relationship"""
        main_part_id = self.main_part_combo.currentData()
        alt_part_id = self.alt_part_combo.currentData()
        
        if main_part_id == alt_part_id:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic("لا يمكن ربط القطعة بنفسها"))
            return
        
        # Check if already exists
        check_query = """
            SELECT COUNT(*) FROM part_alternatives 
            WHERE part_id = ? AND alternative_part_id = ? AND is_deleted = 0
        """
        result = self.db.execute_query(check_query, (main_part_id, alt_part_id))
        
        if result and result[0][0] > 0:
            QMessageBox.warning(self, format_arabic("خطأ"), 
                              format_arabic("هذا البديل مسجل بالفعل"))
            return
        
        # Add both directions (bidirectional relationship)
        query = "INSERT INTO part_alternatives (part_id, alternative_part_id) VALUES (?, ?)"
        result1 = self.db.execute_update(query, (main_part_id, alt_part_id))
        result2 = self.db.execute_update(query, (alt_part_id, main_part_id))
        
        if result1 > 0 and result2 > 0:
            QMessageBox.information(self, format_arabic("نجح"), 
                                  format_arabic("تمت إضافة البديل بنجاح"))
            self.refresh()
        else:
            QMessageBox.critical(self, format_arabic("خطأ"), 
                               format_arabic("فشل في إضافة البديل"))
    
    def search_alternatives(self):
        """Search for alternatives of selected part"""
        part_id = self.search_part_combo.currentData()
        
        query = """
            SELECT p.id, p.part_name, p.brand, p.price, p.quantity
            FROM parts p
            JOIN part_alternatives pa ON p.id = pa.alternative_part_id
            WHERE pa.part_id = ? AND pa.is_deleted = 0 AND p.is_deleted = 0
        """
        alternatives = self.db.execute_query(query, (part_id,))
        
        self.results_table.setRowCount(len(alternatives))
        for row, alt in enumerate(alternatives):
            for col, value in enumerate(alt):
                item = QTableWidgetItem(str(value))
                item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
                self.results_table.setItem(row, col, item)
        
        if len(alternatives) == 0:
            QMessageBox.information(self, format_arabic("نتيجة"), 
                                  format_arabic("لا توجد بدائل لهذه القطعة"))
    
    def refresh(self):
        """Refresh alternatives table"""
        query = """
            SELECT 
                p1.part_name || ' - ' || p1.brand,
                p2.part_name || ' - ' || p2.brand,
                pa.created_at,
                pa.id
            FROM part_alternatives pa
            JOIN parts p1 ON pa.part_id = p1.id
            JOIN parts p2 ON pa.alternative_part_id = p2.id
            WHERE pa.is_deleted = 0
            ORDER BY pa.id DESC
        """
        alternatives = self.db.execute_query(query)
        
        # Remove duplicates (since we store bidirectional)
        seen = set()
        unique_alternatives = []
        for alt in alternatives:
            key = tuple(sorted([alt[0], alt[1]]))
            if key not in seen:
                seen.add(key)
                unique_alternatives.append(alt)
        
        self.alternatives_table.setRowCount(len(unique_alternatives))
        for row, alt in enumerate(unique_alternatives):
            for col in range(3):
                item = QTableWidgetItem(str(alt[col]))
                item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
                self.alternatives_table.setItem(row, col, item)
            
            # Delete button
            delete_btn = QPushButton(format_arabic("حذف"))
            delete_btn.clicked.connect(lambda checked, a_id=alt[3]: self.delete_alternative(a_id))
            self.alternatives_table.setCellWidget(row, 3, delete_btn)
    
    def delete_alternative(self, alt_id: int):
        """Delete alternative relationship"""
        reply = QMessageBox.question(
            self,
            format_arabic("تأكيد الحذف"),
            format_arabic("هل أنت متأكد من حذف هذا البديل؟"),
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No
        )
        
        if reply == QMessageBox.StandardButton.Yes:
            if self.db.soft_delete("part_alternatives", alt_id):
                QMessageBox.information(self, format_arabic("نجح"), 
                                      format_arabic("تم حذف البديل"))
                self.refresh()
            else:
                QMessageBox.critical(self, format_arabic("خطأ"), 
                                   format_arabic("فشل في حذف البديل"))

class RestoreWidget(QWidget):
    """Legacy data restore wizard"""
    
    def __init__(self, db: Database):
        super().__init__()
        self.db = db
        self.init_ui()
    
    def init_ui(self):
        """Initialize restore UI"""
        layout = QVBoxLayout(self)
        
        # Title
        title = QLabel(format_arabic("معالج استعادة البيانات"))
        title.setStyleSheet(f"font-size: 16pt; font-weight: bold; color: {COLOR_RED};")
        layout.addWidget(title)
        
        # Instructions
        info = QLabel(format_arabic(
            "استخدم هذه الأداة لاستيراد البيانات من ملفات قديمة\n"
            "الصيغ المدعومة: JSON, CSV, SQLite"
        ))
        info.setStyleSheet("font-size: 12pt;")
        info.setWordWrap(True)
        layout.addWidget(info)
        
        # File selection
        file_group = QGroupBox(format_arabic("اختيار الملف"))
        file_layout = QVBoxLayout()
        
        file_select_layout = QHBoxLayout()
        self.file_path_label = QLabel(format_arabic("لم يتم اختيار ملف"))
        file_select_layout.addWidget(self.file_path_label)
        
        select_file_btn = QPushButton(format_arabic("اختيار ملف"))
        select_file_btn.clicked.connect(self.select_file)
        file_select_layout.addWidget(select_file_btn)
        
        file_layout.addLayout(file_select_layout)
        
        # Import button
        self.import_btn = QPushButton(format_arabic("استيراد البيانات"))
        self.import_btn.clicked.connect(self.import_data)
        self.import_btn.setEnabled(False)
        file_layout.addWidget(self.import_btn)
        
        file_group.setLayout(file_layout)
        layout.addWidget(file_group)
        
        # Log area
        log_group = QGroupBox(format_arabic("سجل الاستيراد"))
        log_layout = QVBoxLayout()
        
        self.log_text = QTextEdit()
        self.log_text.setReadOnly(True)
        log_layout.addWidget(self.log_text)
        
        log_group.setLayout(log_layout)
        layout.addWidget(log_group)
        
        layout.addStretch()
        
        self.selected_file = None
    
    def select_file(self):
        """Select file to import"""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            format_arabic("اختر ملف البيانات"),
            "",
            "All Files (*.json *.csv *.db *.sqlite);;JSON Files (*.json);;CSV Files (*.csv);;SQLite Files (*.db *.sqlite)"
        )
        
        if file_path:
            self.selected_file = file_path
            self.file_path_label.setText(os.path.basename(file_path))
            self.import_btn.setEnabled(True)
            self.log(f"تم اختيار الملف: {file_path}")
    
    def log(self, message: str):
        """Add message to log"""
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.log_text.append(f"[{timestamp}] {message}")
    
    def import_data(self):
        """Import data from selected file"""
        if not self.selected_file:
            return
        
        try:
            self.log(format_arabic("بدء عملية الاستيراد..."))
            
            file_ext = os.path.splitext(self.selected_file)[1].lower()
            
            if file_ext == '.json':
                self.import_json()
            elif file_ext == '.csv':
                self.import_csv()
            elif file_ext in ['.db', '.sqlite']:
                self.import_sqlite()
            else:
                self.log(format_arabic("صيغة الملف غير مدعومة"))
                QMessageBox.warning(self, format_arabic("خطأ"), 
                                  format_arabic("صيغة الملف غير مدعومة"))
                
        except Exception as e:
            self.log(f"خطأ: {str(e)}")
            QMessageBox.critical(self, format_arabic("خطأ"), 
                               format_arabic(f"فشل الاستيراد: {str(e)}"))
    
    def import_json(self):
        """Import from JSON file"""
        try:
            with open(self.selected_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
            
            # Import parts
            if 'parts' in data:
                for part in data['parts']:
                    query = """
                        INSERT INTO parts (part_name, brand, price, cost, quantity)
                        VALUES (?, ?, ?, ?, ?)
                    """
                    self.db.execute_update(query, (
                        part.get('name', ''),
                        part.get('brand', ''),
                        part.get('price', 0),
                        part.get('cost', 0),
                        part.get('quantity', 0)
                    ))
                self.log(f"تم استيراد {len(data['parts'])} قطعة")
            
            # Import suppliers
            if 'suppliers' in data:
                for supplier in data['suppliers']:
                    query = """
                        INSERT INTO suppliers (supplier_name, contact_info, balance)
                        VALUES (?, ?, ?)
                    """
                    self.db.execute_update(query, (
                        supplier.get('name', ''),
                        supplier.get('contact', ''),
                        supplier.get('balance', 0)
                    ))
                self.log(f"تم استيراد {len(data['suppliers'])} مورد")
            
            self.log(format_arabic("اكتمل الاستيراد بنجاح"))
            QMessageBox.information(self, format_arabic("نجح"), 
                                  format_arabic("تم استيراد البيانات بنجاح"))
            
        except Exception as e:
            raise Exception(f"JSON import error: {str(e)}")
    
    def import_csv(self):
        """Import from CSV file"""
        try:
            import csv
            
            with open(self.selected_file, 'r', encoding='utf-8') as f:
                reader = csv.DictReader(f)
                count = 0
                
                for row in reader:
                    # Try to import as parts
                    if 'part_name' in row or 'name' in row:
                        query = """
                            INSERT INTO parts (part_name, brand, price, cost, quantity)
                            VALUES (?, ?, ?, ?, ?)
                        """
                        self.db.execute_update(query, (
                            row.get('part_name', row.get('name', '')),
                            row.get('brand', ''),
                            float(row.get('price', 0)),
                            float(row.get('cost', 0)),
                            int(row.get('quantity', 0))
                        ))
                        count += 1
                
                self.log(f"تم استيراد {count} سجل من CSV")
                QMessageBox.information(self, format_arabic("نجح"), 
                                      format_arabic(f"تم استيراد {count} سجل"))
                
        except Exception as e:
            raise Exception(f"CSV import error: {str(e)}")
    
    def import_sqlite(self):
        """Import from SQLite file"""
        try:
            # Connect to source database
            source_conn = sqlite3.connect(self.selected_file)
            source_cursor = source_conn.cursor()
            
            # Get list of tables
            source_cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
            tables = source_cursor.fetchall()
            
            total_records = 0
            
            for table in tables:
                table_name = table[0]
                
                # Skip system tables
                if table_name.startswith('sqlite_'):
                    continue
                
                try:
                    # Get all records from table
                    source_cursor.execute(f"SELECT * FROM {table_name}")
                    records = source_cursor.fetchall()
                    
                    # Get column names
                    source_cursor.execute(f"PRAGMA table_info({table_name})")
                    columns = [col[1] for col in source_cursor.fetchall()]
                    
                    # Try to insert into our database
                    # This is a simple approach - may need mapping
                    for record in records:
                        # Check if table exists in our schema
                        check_table = f"SELECT name FROM sqlite_master WHERE type='table' AND name='{table_name}'"
                        if self.db.execute_query(check_table):
                            placeholders = ','.join(['?' for _ in record])
                            insert_query = f"INSERT OR IGNORE INTO {table_name} VALUES ({placeholders})"
                            self.db.execute_update(insert_query, record)
                            total_records += 1
                    
                    self.log(f"استيراد جدول {table_name}: {len(records)} سجل")
                    
                except Exception as e:
                    self.log(f"تخطي جدول {table_name}: {str(e)}")
                    continue
            
            source_conn.close()
            
            self.log(f"تم استيراد إجمالي {total_records} سجل")
            QMessageBox.information(self, format_arabic("نجح"), 
                                  format_arabic(f"تم استيراد {total_records} سجل"))
            
        except Exception as e:
            raise Exception(f"SQLite import error: {str(e)}")

# Main application entry point
def main():
    """Main application entry point"""
    app = QApplication(sys.argv)
    
    # Set application-wide font
    font = QFont("Arial", 12)
    app.setFont(font)
    
    # Create and show main window
    window = MainWindow()
    window.show()
    
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
