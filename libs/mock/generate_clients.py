# typedef struct{
#     int id;
#     char nome[50];
#     char nascimento[11];
# }cliente;

import requests, random, numpy

class Client:

    def __init__(self, id, name, birth_date):
        self.id         = id
        self.name       = name
        self.birth_date = birth_date

    def to_stream(self, file):


        self.name       = self.name       + (50 - len(self.name))       * '\0'
        self.birth_date = self.birth_date + (11 - len(self.birth_date)) * '\0'

        file.write(numpy.int32(self.id))
        file.write(self.name.encode('ascii'))
        file.write(self.birth_date.encode('ascii'))

    def __str__(self):
        return f"{self.id} -> {self.name} -> {self.birth_date}"

def generate_file(size):
    people = []

    for i in range(size):
        response   = requests.get('https://api.namefake.com')
        name       = response.json()['name']
        birth_date = response.json()['birth_data']
        id         = i

        people.append(Client(id, name, birth_date))
        print(people[-1])

    random.shuffle(people)
    newFile = open("db.dat", "wb")
    for person in people:
        person.to_stream(newFile)
    newFile.close()


generate_file(50)



