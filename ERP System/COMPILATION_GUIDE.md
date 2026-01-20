# دليل تحويل البرنامج إلى EXE
# Guide to Compile ERP System to Standalone Windows EXE

## متطلبات التحويل / Requirements

### 1. Install Python
Download and install Python 3.8 or higher from python.org
Make sure to check "Add Python to PATH" during installation

### 2. Install Dependencies
Open Command Prompt and run:
```bash
pip install -r requirements.txt
pip install pyinstaller
```

## طريقة التحويل / Compilation Methods

### Method 1: Basic Single File EXE (الطريقة الأساسية)
```bash
pyinstaller --onefile --windowed --name "QasedKareem-ERP" auto_parts_erp.py
```

### Method 2: With Icon (مع أيقونة)
First, create or download an icon file (app_icon.ico), then:
```bash
pyinstaller --onefile --windowed --icon=app_icon.ico --name "QasedKareem-ERP" auto_parts_erp.py
```

### Method 3: Advanced with All Options (الطريقة المتقدمة)
```bash
pyinstaller --onefile ^
    --windowed ^
    --name "QasedKareem-ERP" ^
    --icon=app_icon.ico ^
    --add-data "database.py;." ^
    --noconsole ^
    auto_parts_erp.py
```

## الخيارات المستخدمة / Options Explained

- `--onefile`: Creates a single executable file
- `--windowed` or `--noconsole`: No console window (GUI only)
- `--name`: Name of the output executable
- `--icon`: Add custom icon to the EXE
- `--add-data`: Include additional files (format: "source;destination")

## بعد التحويل / After Compilation

The EXE file will be located in the `dist` folder:
```
dist/QasedKareem-ERP.exe
```

## توزيع البرنامج / Distribution

You can distribute just the EXE file from the dist folder.
The database file will be created automatically on first run.

## ملاحظات مهمة / Important Notes

1. **First Run**: The first time you run the EXE, it may take a few seconds to start
2. **Database**: The database file (qased_kareem_erp.db) will be created in the same directory as the EXE
3. **Images**: If using part images, make sure the "part_images" folder is in the same directory
4. **Labels**: Barcode labels will be saved in the "labels" folder
5. **Antivirus**: Some antivirus programs may flag PyInstaller executables. Add an exception if needed

## استكشاف الأخطاء / Troubleshooting

### Error: "Failed to execute script"
- Run in non-windowed mode first to see errors:
  ```bash
  pyinstaller --onefile --name "QasedKareem-ERP" auto_parts_erp.py
  ```

### Error: "Module not found"
- Make sure all dependencies are installed:
  ```bash
  pip install -r requirements.txt
  ```

### Large EXE Size
- The EXE will be approximately 50-100 MB due to PyQt6 and other dependencies
- This is normal and necessary for a standalone application

## اختبار البرنامج / Testing

Before compiling, test the program:
```bash
python auto_parts_erp.py
```

## تحديث البرنامج / Updating

When you make changes:
1. Modify the Python source files
2. Test with Python
3. Recompile with PyInstaller
4. Distribute the new EXE

## الدعم الفني / Support

If you encounter issues:
1. Check Python version (3.8+)
2. Verify all dependencies are installed
3. Run in non-windowed mode to see error messages
4. Check PyInstaller documentation: https://pyinstaller.org

---

## Quick Start (البداية السريعة)

For the fastest compilation:

1. Open Command Prompt in the project directory
2. Run:
   ```bash
   pip install pyinstaller
   pyinstaller --onefile --windowed --name "QasedKareem-ERP" auto_parts_erp.py
   ```
3. Find your EXE in the `dist` folder
4. Copy the EXE to any location and run it

That's it! Your standalone ERP system is ready to use.
