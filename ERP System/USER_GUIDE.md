# دليل المستخدم - نظام قاصد كريم لقطع غيار السيارات
# User Guide - Qased Kareem Auto Parts ERP System

## مقدمة / Introduction

نظام قاصد كريم هو نظام متكامل لإدارة محلات قطع غيار السيارات مع دعم كامل للغة العربية.

Qased Kareem is a comprehensive ERP system for auto parts management with full Arabic language support.

---

## الوحدات الرئيسية / Main Modules

### 1. لوحة التحكم / Dashboard
- عرض مؤشرات الأداء الرئيسية (KPIs)
- إجمالي المبيعات
- صافي الربح
- إجمالي المصروفات
- عدد الأصناف في المخزن
- تحذيرات المخزون المنخفض

**How to use:**
- The dashboard updates automatically when you make sales or add expenses
- All values start at zero for a fresh installation
- Click on the "لوحة التحكم" tab to view statistics

---

### 2. المخزن والصور / Inventory & Imaging

**إضافة قطعة جديدة / Adding a New Part:**

1. Fill in the part details:
   - اسم القطعة (Part Name): e.g., "فلتر زيت"
   - الماركة (Brand): e.g., "Toyota"
   - السعر (Price): Selling price in EGP
   - التكلفة (Cost): Purchase cost in EGP
   - الكمية (Quantity): Stock quantity
   - ماركة السيارة (Car Brand): Select from dropdown
   - موديل السيارة (Car Model): e.g., "Corolla"
   - السنوات (Years): e.g., "2020-2025"

2. Click "اختيار صورة" to upload an image of the part (optional)

3. Click "إضافة قطعة" to add the part

**Features:**
- Auto-generated barcode for each part
- Image support for visual identification
- Car brand/model filtering
- Year range specification

---

### 3. المبيعات / Sales

**تسجيل بيع / Recording a Sale:**

1. Select the part from dropdown (shows available parts only)
2. Enter quantity to sell
3. Select sale date (defaults to today)
4. Click "تسجيل البيع"

**What happens:**
- Part quantity is automatically reduced
- Sale is recorded with profit calculation
- Dashboard statistics are updated
- Transaction is logged for audit

---

### 4. المصاريف اليومية / Daily Small Expenses

**إضافة مصروف / Adding an Expense:**

1. Select expense type:
   - طعام (Food)
   - شاي (Tea)
   - تنظيف (Cleaning)
   - سلف موظفين (Staff Advances)
   - مواصلات (Transportation)
   - أخرى (Other)

2. Enter amount in EGP
3. Add description (optional)
4. Select date (defaults to today)
5. Click "إضافة مصروف"

**Note:** Expenses are deducted from net profit automatically.

---

### 5. حسابات الموردين / Supplier Ledger

**إضافة مورد / Adding a Supplier:**

1. Enter supplier name
2. Enter contact information
3. Click "إضافة مورد"

**إضافة معاملة / Adding a Transaction:**

1. Click on a supplier in the table
2. Select transaction type:
   - شراء (Purchase): Increases supplier balance
   - دفع (Payment): Decreases supplier balance
3. Enter amount
4. Add description
5. Select date
6. Click "إضافة معاملة"

**Features:**
- Real-time balance tracking
- Complete transaction history
- Multiple suppliers support

---

### 6. الباركود / Barcode

**طباعة ملصق / Printing a Label:**

1. Search for a part using the search box
2. Click "طباعة" button next to the part
3. A PDF label will be generated in the "labels" folder
4. The label includes:
   - Company name (Qased Kareem)
   - Part name and brand
   - Price
   - Barcode number

**Note:** Labels are saved as PDF files that can be printed on standard label printers.

---

### 7. بدائل القطع / Cross-Reference (Alternatives)

**ربط قطعة ببديلها / Linking Alternative Parts:**

1. Select the main part from first dropdown
2. Select the alternative part from second dropdown
3. Click "إضافة بديل"

**البحث عن بدائل / Searching for Alternatives:**

1. Select a part from the search dropdown
2. Click "بحث عن البدائل"
3. View available alternatives with prices and stock

**Use case:** When a customer asks for a part that's out of stock, the system can suggest compatible alternatives.

---

### 8. استعادة البيانات / Legacy Restore Wizard

**استيراد بيانات قديمة / Importing Old Data:**

1. Click "اختيار ملف"
2. Select your data file (JSON, CSV, or SQLite)
3. Click "استيراد البيانات"
4. Check the import log for results

**Supported Formats:**
- **JSON**: Parts and suppliers
- **CSV**: Parts data
- **SQLite**: Complete database import

**Example JSON Format:**
```json
{
  "parts": [
    {
      "name": "فلتر زيت",
      "brand": "Toyota",
      "price": 150.0,
      "cost": 100.0,
      "quantity": 10
    }
  ],
  "suppliers": [
    {
      "name": "مورد قطع الغيار",
      "contact": "0123456789",
      "balance": 5000.0
    }
  ]
}
```

---

## الميزات الأمنية / Security Features

### Soft Delete (الحذف الآمن)
- All deletions are logged in the audit table
- No actual data loss occurs
- Deleted items are marked as "is_deleted = 1"
- Audit log tracks who deleted what and when

### Atomic Transactions (المعاملات الذرية)
- All database operations use transactions
- Either all changes succeed or none do
- Prevents data corruption
- Ensures data integrity

---

## نصائح الاستخدام / Usage Tips

1. **Backup Regularly**: Copy the `qased_kareem_erp.db` file to a safe location
2. **Start Fresh**: The database starts empty - add your data gradually
3. **Images**: Store part images for better identification during sales
4. **Barcode Labels**: Print labels for popular parts to speed up checkout
5. **Daily Expenses**: Record all small expenses to get accurate profit calculations
6. **Alternatives**: Set up alternatives for frequently requested parts
7. **Supplier Tracking**: Keep supplier balances updated to manage cash flow

---

## استكشاف الأخطاء / Troubleshooting

### Problem: Application won't start
- **Solution**: Make sure all dependencies are installed (run: `pip install -r requirements.txt`)

### Problem: Arabic text not displaying correctly
- **Solution**: Make sure `arabic-reshaper` and `python-bidi` are installed

### Problem: Database errors
- **Solution**: Delete the database file and restart (note: this will delete all data)

### Problem: Barcode labels not generating
- **Solution**: Make sure `reportlab` is installed and you have write permissions

---

## معلومات تقنية / Technical Information

- **Database**: SQLite (qased_kareem_erp.db)
- **Images Folder**: part_images/
- **Labels Folder**: labels/
- **Language**: Python 3.8+
- **Framework**: PyQt6
- **RTL Support**: arabic-reshaper, python-bidi

---

## الدعم / Support

For issues, questions, or feature requests, refer to:
- README_ERP.md for overview
- COMPILATION_GUIDE.md for building EXE
- test_system.py for system diagnostics

---

## رخصة الاستخدام / License

This is a professional ERP system built specifically for auto parts management.
All rights reserved.

---

**تم إنشاء هذا النظام خصيصاً لمحلات قطع غيار السيارات**
**This system was built specifically for auto parts shops**

---

© 2026 Qased Kareem Auto Parts ERP System
