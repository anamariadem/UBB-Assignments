import unittest
from domain import *
from exceptions import *
from repository import *
from service import *
from undoController import *

class Tests(unittest.TestCase):
    def test_create_student(self):
        s = Student(2710,"Ana")
        self.assertEqual(str(s), "ID:  2710  Name: Ana")
        self.assertEqual(s.StudId,2710)
        #assert s.StudId == 2710
        assert s.StudName == "Ana"
        s.StudName = "Marie"
        assert s.StudName == 'Marie'
        try:
            s.StudName = "12na"
        except StudentValueException:
            assert True

    def test_create_discipline(self):
        d = Discipline(2,'Math')
        self.assertEqual(str(d),"ID:  2    Name: Math")
        assert d.DiscId == 2
        assert d.DiscName == 'Math'
        d.DiscName = 'Science'
        assert d.DiscName == 'Science'

    def test_grade(self):
        g = Grade(2710,2,6)
        self.assertEqual(str(g),"Student ID: 2710  Discipline ID: 2   Grade: 6")
        assert g.StudId == 2710
        assert g.DiscId == 2
        assert g.GradeValue == 6
        g.GradeValue = 7
        assert g.GradeValue == 7
        try:
            g.GradeValue = 12
        except GradeValueException:
            assert True

    def test_repo_add(self):
        r = Repository()
        self.assertEqual(0,len(r))
        s = Student(2710, "Ana")
        r.add(s)
        self.assertEqual(1,len(r))
        self.assertRaises(StudentValueException,r.add ,s)

    def test_repo_isDuplicate(self):
        r = Repository()
        self.assertEqual(0, len(r))
        s = Student(2710, "Ana")
        r.add(s)
        s2 = Student(2711, "Marie")
        idx1 = r.isDuplicate(s2)
        self.assertEqual(1,idx1)
        s3 = Student(2710, "Ana")
        idx = r.isDuplicate(s3)
        self.assertEqual(0,idx)
        s4 = Student(2713, "Ana")
        idx = r.isDuplicate(s4)
        self.assertEqual(0,idx)

    def test_repo_find(self):
        r = Repository()
        self.assertEqual(0, len(r))
        s = Student(2710, "Ana")
        r.add(s)
        self.assertEqual(s,r.find(2710))
        self.assertRaises(StudentValueException, r.find, 2711)

    def test_repo_modify_name(self):
        r = Repository()
        self.assertEqual(0, len(r))
        s = Student(2710, "Ana")
        r.add(s)
        r.modify_name(2710,"Marie")
        self.assertEqual(s.StudName,"Marie")
        self.assertRaises(StudentValueException,r.modify_name,2711,'abc')

    def test_repo_remove(self):
        r = Repository()
        self.assertEqual(0, len(r))
        s = Student(2710, "Ana")
        r.add(s)
        r.remove(2710)
        self.assertEqual(0,len(r))
        self.assertRaises(StudentValueException,r.remove,2771)

    def test_search(self):
        r = Repository()
        l = r.getAll()
        self.assertEqual(0,len(l))
        s = Student(1,"Anna-Maria")
        r.add(s)
        s2 = Student(2,"Andra")
        r.add(s2)
        l = r.search_by_name("An")
        self.assertEqual(2,len(l))
        self.assertRaises(StudentValueException, r.search_by_name, 'zz')

    def test_grade_add(self):
        r1 = GradeRepository()
        students = [Student(2710,"Ana")]
        disciplines = [Discipline(1,"Math")]
        grade = Grade(2710,1,9)
        r1.add(grade,students,disciplines)
        self.assertEqual(1,len(r1))
        grade = Grade(2711,6,8)
        self.assertRaises(GradeValueException,r1.add, grade,students,disciplines)

    def test_grade_remove(self):
        r1 = GradeRepository()
        students = [Student(2710, "Ana"),Student(2711,"Marie")]
        disciplines = [Discipline(1, "Math"), Discipline(2,"Logic")]
        grade = Grade(2710, 1, 9)
        r1.add(grade, students, disciplines)
        grade2 = Grade(2711,2,7)
        r1.add(grade2,students,disciplines)
        self.assertEqual(2,len(r1))
        r1.removeG("s",2710)
        self.assertEqual(1,len(r1))
        r1.removeG("d",2)
        self.assertEqual(0,len(r1))
        list = r1.getAll()
        self.assertEqual(0,len(list))
        self.assertRaises(GradeValueException, r1.removeG, 'a',2)

    def test_service_addS(self):
        r = Repository()
        s = StudentService(r)
        list = s.getAll()
        self.assertEqual(0,len(list))
        id = 2701
        name = "Ana"
        s.add(id,name)
        self.assertEqual(1,len(list))
        id = 2701
        name = "Maria"
        self.assertRaises(StudentValueException, s.add, id, name)

    def test_service_modify_n(self):
        r = Repository()
        s = StudentService(r)
        list = s.getAll()
        id = 2701
        name = "Ana"
        s.add(id, name)
        s.modify_name(2701, "Maria")
        self.assertEqual(list[0].StudName, "Maria")
        self.assertRaises(StudentValueException,s.modify_name,2702,"abc")

    def test_service_remove(self):
        r = Repository()
        s = StudentService(r)
        list = s.getAll()
        id = 2701
        name = "Ana"
        s.add(id, name)
        s.remove(2701)
        self.assertEqual(len(list),0)
        self.assertRaises(StudentValueException, s.remove, 2702)

    def test_service_find(self):
        r = Repository()
        s = StudentService(r)
        list = s.getAll()
        id = 2701
        name = "Ana"
        s.add(id, name)
        self.assertEqual(list[0],s.find(2701))
        self.assertRaises(StudentValueException, s.find, 2702)

    def test_service_search(self):
        r = Repository()
        s = StudentService(r)
        list = s.getAll()
        id = 2701
        name = "Ana"
        s.add(id, name)
        l = s.search_by_name("a")
        self.assertEqual(len(l),1)
        self.assertRaises(StudentValueException, s.search_by_name, "z")

    def test_discipline_addD(self):
        r = Repository()
        s = DisciplineService(r)
        list = s.getAll()
        self.assertEqual(0, len(list))
        id = 2
        name = "English"
        s.add(id, name)
        self.assertEqual(1, len(list))
        id = 2
        name = "Maria"
        self.assertRaises(DisciplineValueException, s.add, id,name)

    def test_service_modify_d(self):
        r = Repository()
        s = DisciplineService(r)
        list = s.getAll()
        id = 27
        name = "Math Analysis"
        s.add(id, name)
        s.modify_name(27, "geometry")
        self.assertEqual(list[0].DiscName, "geometry")
        self.assertRaises(DisciplineValueException,s.modify_name,2702,"abc")

    def test_service_removeD(self):
        r = Repository()
        s = DisciplineService(r)
        list = s.getAll()
        id = 27
        name = "Math"
        s.add(id, name)
        s.remove(27)
        self.assertEqual(len(list),0)
        self.assertRaises(DisciplineValueException, s.remove, 2702)

    def test_service_findD(self):
        r = Repository()
        s = DisciplineService(r)
        list = s.getAll()
        id = 27
        name = "Math"
        s.add(id, name)
        self.assertEqual(list[0],s.find(27))
        self.assertRaises(DisciplineValueException, s.find, 2702)

    def test_service_searchD(self):
        r = Repository()
        s = DisciplineService(r)
        list = s.getAll()
        id = 27
        name = "Math"
        s.add(id, name)
        l = s.search_by_name("a")
        self.assertEqual(len(l),1)
        self.assertRaises(DisciplineValueException, s.search_by_name, "z")



