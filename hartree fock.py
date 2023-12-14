import math
import matplotlib.pyplot as plt

class System : 
    def __init__(self):
        self.nuc = []
        self.elec = []

        self.x = -10 
        self.y = 10 
        self.dx = 0.01

    def p_sys(self, data) :
        if type(data[0]) == type([]):
            for i in data:
                plt.plot(i)
        else:
            plt.plot(data)
        plt.show()


    def e_pot(self,gto):
        i_x = self.x
        summe = 0

        while i_x < self.y:
            summe += (gto.sto_radial(i_x)) * self.dx / (abs(i_x)) #wie nimmt potentielle energie ab normalerweise expotetntiell
            i_x += self.dx

        return summe
    
    def e_kin(self, gto):
        i_x = self.x
        summe = 0

        while i_x < self.y:
            summe += abs(gto.dx2_sto(i_x)) * self.dx #hoch 2 kreis auchtung i_x**2 nicht aleine, remove negativ values
            i_x += self.dx

        return summe*0.5
    
    def e_c(self,gto, gto2):
        i_x = self.x
        summe = 0

        while i_x < self.y:
            summe += abs(gto.sto(i_x)**2) 
            i_x += self.dx
        
        return summe
    
    def e_h(self, gto):
        e = self.e_kin(gto) + self.e_pot(gto)
        #print(str(round(self.e_kin(gto),5)) + " " + str(round(self.e_pot(gto),5)))
        return e
    
    def derive_e(self,gto, dx):
        e1 = self.e_h(gto)
        #print(gto.z)
        gto.set_z(gto.z + dx)
        #gto.z += dx
        e2 = self.e_h(gto)
        gto.set_z(gto.z - dx)
        #gto.z -= dx
        s = str(e1) + " " + str(e2)
        #print(s)

        return (e1-e2) #normal - (e2-e1)
    
    def min_e_gto(self,gto):
        data = []
        de : float = 0.01
        c : int = 0

        while abs(de) > 1e-9 and c < 100:
            de = self.derive_e(gto,self.dx)*self.dx
            #gto.z += 0.01 * self.step(de) #mit 2
            #print(de)
            gto.set_z(gto.z + de)
            #gto.z += de

            e = self.e_h(gto)

            o_str = str(c) + " " + str(round(e,9)) + " " + str(round(de,9)) + " " + str(round(gto.z,2))
            #print(o_str)

            data.append(e)

            c += 1

        gto.set_z(gto.z)
        return data
    
    def min_e_aux(self,gto):
        data = []
        for i in range(10):
            data.append(self.min_e_gto(gto))
            #data.append(self.e_h(gto))
            print(str(self.e_h(gto)) + " " + str(gto.z))
        return data
    
    def e_scan(self, x, y, dx, gto):
        old_z = gto.z
        data = []
        while x < y:
            gto.set_z(x)
            #gto.z = x
            data.append(self.e_h(gto))
            x += dx
        gto.set_z(old_z)
        return data

    def test_s(self):
        n = Nuc(1,0)
        e = gto(0,0.1) 
        #e2 = gto(0,0.1)

        data = self.min_e_aux(e)
        #data = self.min_e_gto(e)
        print(self.e_h(e))

        #data = self.e_scan(1,4,0.02,e)

        #data = e.get_pos(-10,10,0.1)
        #data2 = e2.get_pos(-5,5,0.1)
        self.p_sys(data)


class Nuc :
    def __init__(self, n ,cord):
        self.n = n
        self.cord = cord

class gto : 
    def __init__(self, pos, zeta):
        self.pos = pos
        self.norm = 1
        self.z = zeta

        self.set_norm()

    def set_norm(self):
        self.norm = math.sqrt(self.get_self_overlap(-20, 20, 0.01))
    
    def set_z(self,z):
        self.z = abs(z)
        self.set_norm()

    def gto_sto(self, r):
        r = abs(r)
        return (math.e ** (-self.z*(r**2)))/self.norm
    
    def dx_gto_sto(self,r):
        r = abs(r)
        return -2*self.z*r*self.gto_sto(r)
    
    def dx2_gto_sto(self,r):
        r = abs(r)
        return 2*self.z*self.gto_sto(r)*(2*(r**2)*self.z - 1)
    
    def sto(self,r):
        r = abs(r)
        return math.e**(-self.z*r)/self.norm
    
    def dx_sto(self,r):
        r = abs(r)
        return -self.z * self.sto(r)
    
    def dx2_sto(self,r):
        r = abs(r)
        return self.z**2 * self.sto(r)
    
    def gto_radial(self, r):
        return self.gto_sto(r)*(r**2)
    
    def sto_radial(self,r):
        return self.sto(r)*(r**2)

    def get_self_overlap(self,x,y,dx):
        summe = 0
        while x < y:
            summe += (self.sto(x))**2 * dx
            x += dx
        return summe
    
    def get_value(self,x,y,dx):
        summe = 0
        while x < y:
            summe += self.sto(x) * dx
            x += dx
        return summe
    
    def get_pos(self, x, y, dx):
        pos = []
        while x < y:
            pos.append(self.sto(x))
            x += dx
        return pos

s = System()
s.test_s();
#g = gto(0,0.1)
#print(g.get_value(-20,20,0.01))