"""
Database module for Qased Kareem Auto Parts ERP System
Handles all SQLite database operations with atomic transactions
"""

import sqlite3
import os
from datetime import datetime
from typing import Optional, List, Tuple, Any

class Database:
    """Database handler with SQLite and atomic transactions"""
    
    def __init__(self, db_name: str = "qased_kareem_erp.db"):
        """Initialize database connection"""
        self.db_name = db_name
        self.conn: Optional[sqlite3.Connection] = None
        self.cursor: Optional[sqlite3.Cursor] = None
        self.connect()
        self.create_tables()
    
    def connect(self):
        """Create database connection"""
        try:
            self.conn = sqlite3.connect(self.db_name)
            self.cursor = self.conn.cursor()
            # Enable foreign keys
            self.cursor.execute("PRAGMA foreign_keys = ON")
            self.conn.commit()
        except sqlite3.Error as e:
            print(f"Database connection error: {e}")
            raise
    
    def create_tables(self):
        """Create all necessary tables"""
        try:
            # Parts inventory table
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS parts (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    part_name TEXT NOT NULL,
                    brand TEXT NOT NULL,
                    price REAL NOT NULL,
                    cost REAL NOT NULL,
                    quantity INTEGER NOT NULL DEFAULT 0,
                    image_path TEXT,
                    car_brand TEXT,
                    car_model TEXT,
                    years TEXT,
                    barcode TEXT UNIQUE,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    is_deleted INTEGER DEFAULT 0
                )
            """)
            
            # Car brands table
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS car_brands (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    brand_name TEXT NOT NULL UNIQUE,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    is_deleted INTEGER DEFAULT 0
                )
            """)
            
            # Car models table
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS car_models (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    brand_id INTEGER NOT NULL,
                    model_name TEXT NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    is_deleted INTEGER DEFAULT 0,
                    FOREIGN KEY (brand_id) REFERENCES car_brands(id)
                )
            """)
            
            # Daily expenses table
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS daily_expenses (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    expense_type TEXT NOT NULL,
                    amount REAL NOT NULL,
                    description TEXT,
                    expense_date DATE NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    is_deleted INTEGER DEFAULT 0
                )
            """)
            
            # Supplier ledger table
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS suppliers (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    supplier_name TEXT NOT NULL,
                    contact_info TEXT,
                    balance REAL DEFAULT 0,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    is_deleted INTEGER DEFAULT 0
                )
            """)
            
            # Supplier transactions table
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS supplier_transactions (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    supplier_id INTEGER NOT NULL,
                    transaction_type TEXT NOT NULL,
                    amount REAL NOT NULL,
                    description TEXT,
                    transaction_date DATE NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    is_deleted INTEGER DEFAULT 0,
                    FOREIGN KEY (supplier_id) REFERENCES suppliers(id)
                )
            """)
            
            # Cross-reference (alternatives) table
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS part_alternatives (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    part_id INTEGER NOT NULL,
                    alternative_part_id INTEGER NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    is_deleted INTEGER DEFAULT 0,
                    FOREIGN KEY (part_id) REFERENCES parts(id),
                    FOREIGN KEY (alternative_part_id) REFERENCES parts(id)
                )
            """)
            
            # Sales transactions table
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS sales (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    part_id INTEGER NOT NULL,
                    quantity INTEGER NOT NULL,
                    unit_price REAL NOT NULL,
                    unit_cost REAL NOT NULL,
                    total_price REAL NOT NULL,
                    profit REAL NOT NULL,
                    sale_date DATE NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    is_deleted INTEGER DEFAULT 0,
                    FOREIGN KEY (part_id) REFERENCES parts(id)
                )
            """)
            
            # Audit log table for soft deletes
            self.cursor.execute("""
                CREATE TABLE IF NOT EXISTS audit_log (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    table_name TEXT NOT NULL,
                    record_id INTEGER NOT NULL,
                    action TEXT NOT NULL,
                    old_data TEXT,
                    new_data TEXT,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            """)
            
            self.conn.commit()
        except sqlite3.Error as e:
            print(f"Error creating tables: {e}")
            self.conn.rollback()
            raise
    
    def execute_query(self, query: str, params: tuple = ()) -> List[Tuple]:
        """Execute a SELECT query and return results"""
        try:
            self.cursor.execute(query, params)
            return self.cursor.fetchall()
        except sqlite3.Error as e:
            print(f"Query execution error: {e}")
            return []
    
    def execute_update(self, query: str, params: tuple = ()) -> int:
        """Execute INSERT/UPDATE/DELETE query with atomic transaction"""
        try:
            self.cursor.execute(query, params)
            self.conn.commit()
            return self.cursor.lastrowid
        except sqlite3.Error as e:
            print(f"Update execution error: {e}")
            self.conn.rollback()
            return -1
    
    def soft_delete(self, table_name: str, record_id: int, old_data: str = ""):
        """Soft delete a record and log to audit"""
        # Whitelist of allowed tables for security
        allowed_tables = [
            'parts', 'car_brands', 'car_models', 'daily_expenses',
            'suppliers', 'supplier_transactions', 'part_alternatives', 'sales'
        ]
        
        if table_name not in allowed_tables:
            print(f"Security error: Table '{table_name}' not allowed for soft delete")
            return False
        
        try:
            # Mark as deleted (table_name validated above)
            query = f"UPDATE {table_name} SET is_deleted = 1 WHERE id = ?"
            self.cursor.execute(query, (record_id,))
            
            # Log to audit
            audit_query = """
                INSERT INTO audit_log (table_name, record_id, action, old_data)
                VALUES (?, ?, 'SOFT_DELETE', ?)
            """
            self.cursor.execute(audit_query, (table_name, record_id, old_data))
            
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print(f"Soft delete error: {e}")
            self.conn.rollback()
            return False
    
    def get_dashboard_stats(self) -> dict:
        """Get real-time KPI statistics"""
        try:
            stats = {
                'total_sales': 0.0,
                'net_profit': 0.0,
                'total_expenses': 0.0,
                'parts_count': 0,
                'low_stock_count': 0
            }
            
            # Total sales and profit
            sales_query = """
                SELECT COALESCE(SUM(total_price), 0), COALESCE(SUM(profit), 0)
                FROM sales
                WHERE is_deleted = 0
            """
            result = self.execute_query(sales_query)
            if result:
                stats['total_sales'] = result[0][0]
                stats['net_profit'] = result[0][1]
            
            # Total expenses
            expenses_query = """
                SELECT COALESCE(SUM(amount), 0)
                FROM daily_expenses
                WHERE is_deleted = 0
            """
            result = self.execute_query(expenses_query)
            if result:
                stats['total_expenses'] = result[0][0]
            
            # Adjust profit for expenses
            stats['net_profit'] -= stats['total_expenses']
            
            # Parts count
            parts_query = "SELECT COUNT(*) FROM parts WHERE is_deleted = 0"
            result = self.execute_query(parts_query)
            if result:
                stats['parts_count'] = result[0][0]
            
            # Low stock count (less than 5 items)
            low_stock_query = """
                SELECT COUNT(*) FROM parts 
                WHERE quantity < 5 AND is_deleted = 0
            """
            result = self.execute_query(low_stock_query)
            if result:
                stats['low_stock_count'] = result[0][0]
            
            return stats
        except Exception as e:
            print(f"Error getting dashboard stats: {e}")
            return stats
    
    def close(self):
        """Close database connection"""
        if self.conn:
            self.conn.close()
    
    def __del__(self):
        """Destructor to ensure connection is closed"""
        self.close()
