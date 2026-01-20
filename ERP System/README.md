# نظام قاصد كريم لقطع غيار السيارات
# Qased Kareem Auto Parts ERP System

This directory contains the complete Desktop ERP System for auto parts management.

## Quick Start

```bash
# Navigate to ERP System directory
cd "ERP System"

# Install dependencies
pip install -r requirements.txt

# Run the application
python auto_parts_erp.py

# Run tests
python test_system.py
```

## Compilation to Windows EXE

```bash
cd "ERP System"
pip install pyinstaller
pyinstaller --onefile --windowed --name "QasedKareem-ERP" auto_parts_erp.py
```

The executable will be in the `dist/` folder.

## Documentation

- **README_ERP.md** - Project overview and features
- **USER_GUIDE.md** - Complete user manual (Arabic/English)
- **COMPILATION_GUIDE.md** - Windows EXE build instructions
- **PROJECT_SUMMARY.md** - Technical specifications
- **FINAL_SUMMARY.md** - Project completion summary
- **SECURITY_SUMMARY.md** - Security documentation

## Project Structure

```
ERP System/
├── auto_parts_erp.py       # Main application (8 modules)
├── database.py             # Database handler with security
├── test_system.py          # Automated test suite
├── requirements.txt        # Python dependencies
├── .gitignore              # Git exclusions
└── *.md                    # Documentation files
```

## System Requirements

- Python 3.8 or higher
- Windows 7+ (for compiled EXE)
- 100MB free disk space

## Features

✅ 8 Integrated Modules (Dashboard, Inventory, Sales, Expenses, Suppliers, Barcode, Alternatives, Restore)  
✅ 100% Arabic RTL Interface  
✅ SQLite Database with Atomic Transactions  
✅ Security Hardened (SQL Injection Protected)  
✅ Soft Delete with Audit Logging  
✅ Image Upload for Parts  
✅ PDF Barcode Label Generation  
✅ Legacy Data Import (JSON/CSV/SQLite)  

## Support

For detailed instructions, see **USER_GUIDE.md** in this directory.

---

**Status**: ✅ Production Ready  
**Security**: ✅ All Vulnerabilities Patched  
**Version**: 1.0.0  

© 2026 Qased Kareem Auto Parts ERP System
