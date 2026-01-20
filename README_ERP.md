# نظام قاصد كريم لقطع غيار السيارات
# Qased Kareem Auto Parts ERP System

## Overview
Professional Desktop ERP system for auto parts management with full Arabic (RTL) support.

## Features
- **Inventory & Imaging**: Manage parts with photos
- **Car Brands/Models**: Smart drop-down selectors
- **Years Selection**: Multi-select for production years
- **Daily Small Expenses**: Track daily outgoings
- **Supplier Ledger**: Comprehensive supplier tracking
- **Internal Barcode**: Generate and print labels
- **Cross-Reference**: Compatible alternatives suggestions
- **Dashboard**: Real-time KPIs (Sales, Profit, Expenses)
- **Soft Delete**: Audit log for all deletions
- **Legacy Restore**: Import old data files

## Requirements
- Python 3.8 or higher
- PyQt6
- arabic-reshaper
- python-bidi
- Pillow
- reportlab

## Installation

### For Development
```bash
pip install -r requirements.txt
python auto_parts_erp.py
```

### For Windows Standalone EXE
```bash
# Install PyInstaller
pip install pyinstaller

# Create standalone executable
pyinstaller --onefile --windowed --name "QasedKareem-ERP" --icon=app_icon.ico auto_parts_erp.py

# The EXE will be in the 'dist' folder
```

## Database
The system uses SQLite with automatic initialization. The database file `qased_kareem_erp.db` will be created on first run.

## Usage
1. Run the application
2. Use the main menu to navigate between modules
3. All data is automatically saved to the database
4. The dashboard shows real-time statistics

## Branding
- Colors: Red, Black, White
- Focus: Auto Parts only (no maintenance/service features)
- Language: 100% Arabic with RTL support

## Security
- Atomic SQLite transactions
- Soft delete with audit log
- Data integrity checks
- No data loss guarantees

## Support
For issues or questions, please refer to the documentation in the Documents folder.
