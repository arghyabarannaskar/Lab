public class Department {
    private String deptCode;
    private String deptName;
    private String location;

    public Department(String deptCode, String deptName, String location) {
        this.deptCode = deptCode;
        this.deptName = deptName;
        this.location = location;
    }

    public String getDeptCode() {
        return deptCode;
    }

    public String getDeptName() {
        return deptName;
    }

    public String getLocation() {
        return location;
    }

    @Override
    public String toString() {
        return "Department Code: " + deptCode + ", Name: " + deptName + ", Location: " + location;
    }
}

public class Employee {
    private String empCode;
    private String empName;
    private double basic;
    private String deptCode;

    public Employee(String empCode, String empName, double basic, String deptCode) {
        this.empCode = empCode;
        this.empName = empName;
        this.basic = basic;
        this.deptCode = deptCode;
    }

    public String getEmpCode() {
        return empCode;
    }

    public String getEmpName() {
        return empName;
    }

    public double getBasic() {
        return basic;
    }

    public void setBasic(double basic) {
        this.basic = basic;
    }

    public String getDeptCode() {
        return deptCode;
    }

    @Override
    public String toString() {
        return "Employee Code: " + empCode + ", Name: " + empName + ", Basic: " + basic + ", Dept Code: " + deptCode;
    }
}

import java.util.ArrayList;
import java.util.Comparator;

public class CompanyArrayList {
    private ArrayList<Department> departments;
    private ArrayList<Employee> employees;

    public CompanyArrayList() {
        departments = new ArrayList<>();
        employees = new ArrayList<>();
    }

    public boolean addDepartment(Department department) {
        for (Department dept : departments) {
            if (dept.getDeptCode().equals(department.getDeptCode())) {
                return false;
            }
        }
        departments.add(department);
        return true;
    }

    public boolean addEmployee(Employee employee) {
        for (Department dept : departments) {
            if (dept.getDeptCode().equals(employee.getDeptCode())) {
                for (Employee emp : employees) {
                    if (emp.getEmpCode().equals(employee.getEmpCode())) {
                        return false;
                    }
                }
                employees.add(employee);
                return true;
            }
        }
        return false;
    }

    public Employee getEmployeeByCode(String empCode) {
        for (Employee emp : employees) {
            if (emp.getEmpCode().equals(empCode)) {
                return emp;
            }
        }
        return null;
    }

    public Department getDepartmentByCode(String deptCode) {
        for (Department dept : departments) {
            if (dept.getDeptCode().equals(deptCode)) {
                return dept;
            }
        }
        return null;
    }

    public void displayEmployeeDetails(String empCode) {
        Employee emp = getEmployeeByCode(empCode);
        if (emp != null) {
            System.out.println(emp);
            System.out.println(getDepartmentByCode(emp.getDeptCode()));
        } else {
            System.out.println("Employee not found.");
        }
    }

    public void displayAllEmployees() {
        for (Employee emp : employees) {
            System.out.println(emp);
        }
    }

    public double getTotalBasicByDept(String deptCode) {
        double total = 0;
        for (Employee emp : employees) {
            if (emp.getDeptCode().equals(deptCode)) {
                total += emp.getBasic();
            }
        }
        return total;
    }

    public boolean removeEmployee(String empCode) {
        for (Employee emp : employees) {
            if (emp.getEmpCode().equals(empCode)) {
                employees.remove(emp);
                return true;
            }
        }
        return false;
    }

    public boolean modifyBasic(String empCode, double newBasic) {
        Employee emp = getEmployeeByCode(empCode);
        if (emp != null) {
            emp.setBasic(newBasic);
            return true;
        }
        return false;
    }

    public void sortEmployeesByBasic() {
        employees.sort(Comparator.comparingDouble(Employee::getBasic).reversed());
    }

    public void sortEmployeesByDeptCode() {
        employees.sort(Comparator.comparing(Employee::getDeptCode));
    }

    public void sortEmployeesByEmpCode() {
        employees.sort(Comparator.comparing(Employee::getEmpCode));
    }

    public static void main(String[] args) {
        CompanyArrayList company = new CompanyArrayList();
        // Test the functionality here
    }
}

import java.util.LinkedList;
import java.util.Comparator;

public class CompanyLinkedList {
    private LinkedList<Department> departments;
    private LinkedList<Employee> employees;

    public CompanyLinkedList() {
        departments = new LinkedList<>();
        employees = new LinkedList<>();
    }

    public boolean addDepartment(Department department) {
        for (Department dept : departments) {
            if (dept.getDeptCode().equals(department.getDeptCode())) {
                return false;
            }
        }
        departments.add(department);
        return true;
    }

    public boolean addEmployee(Employee employee) {
        for (Department dept : departments) {
            if (dept.getDeptCode().equals(employee.getDeptCode())) {
                for (Employee emp : employees) {
                    if (emp.getEmpCode().equals(employee.getEmpCode())) {
                        return false;
                    }
                }
                employees.add(employee);
                return true;
            }
        }
        return false;
    }

    public Employee getEmployeeByCode(String empCode) {
        for (Employee emp : employees) {
            if (emp.getEmpCode().equals(empCode)) {
                return emp;
            }
        }
        return null;
    }

    public Department getDepartmentByCode(String deptCode) {
        for (Department dept : departments) {
            if (dept.getDeptCode().equals(deptCode)) {
                return dept;
            }
        }
        return null;
    }

    public void displayEmployeeDetails(String empCode) {
        Employee emp = getEmployeeByCode(empCode);
        if (emp != null) {
            System.out.println(emp);
            System.out.println(getDepartmentByCode(emp.getDeptCode()));
        } else {
            System.out.println("Employee not found.");
        }
    }

    public void displayAllEmployees() {
        for (Employee emp : employees) {
            System.out.println(emp);
        }
    }

    public double getTotalBasicByDept(String deptCode) {
        double total = 0;
        for (Employee emp : employees) {
            if (emp.getDeptCode().equals(deptCode)) {
                total += emp.getBasic();
            }
        }
        return total;
    }

    public boolean removeEmployee(String empCode) {
        for (Employee emp : employees) {
            if (emp.getEmpCode().equals(empCode)) {
                employees.remove(emp);
                return true;
            }
        }
        return false;
    }

    public boolean modifyBasic(String empCode, double newBasic) {
        Employee emp = getEmployeeByCode(empCode);
        if (emp != null) {
            emp.setBasic(newBasic);
            return true;
        }
        return false;
    }

    public void sortEmployeesByBasic() {
        employees.sort(Comparator.comparingDouble(Employee::getBasic).reversed());
    }

    public void sortEmployeesByDeptCode() {
        employees.sort(Comparator.comparing(Employee::getDeptCode));
    }

    public void sortEmployeesByEmpCode() {
        employees.sort(Comparator.comparing(Employee::getEmpCode));
    }

    public static void main(String[] args) {
        CompanyLinkedList company = new CompanyLinkedList();
        // Test the functionality here
    }
}
