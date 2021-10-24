# импорт библиотек
from tkinter import *
from tkinter.ttk import Combobox
from tkinter import messagebox


# основные функции

# алгоритм для подсчета дня недели по дате
def weekday(y: int, m: int, d: int) -> int:
	if m < 3:
		y -= 1
		m += 10
	else:
		m -= 2
	return (d + 31 * m // 12 + y + y // 4 - y // 100 + y // 400) % 7


# вывод дня недели
def clicked():
	messagebox.showinfo('Title', 'Text')


# создание основного окна
window = Tk()
window.geometry('500x350')
window.resizable(0, 0)

# заголовок программы
window.title("Вычисление дня недели по дате")

# текст в окне программы
text_1 = "Выберите дату"
lbl_1 = Label(window, text=text_1)
lbl_1.place(x=90, y=5)

# создание поля для выбора дня
day_list = [x for x in range(1, 32)]
day = Combobox(window, values=day_list, width=3)
day.current(14)
day.place(x=40, y=50)
#day_value = day.get()

# создание поля для выбора месяца
month_dict = {'Январь': 1, 'Февраль': 2, 'Март': 3,
			  'Апрель': 4, 'Май': 5, 'Июнь': 6,
			  'Июль': 7, 'Август': 8, 'Сентябрь': 9,
			  'Октябрь': 10, 'Ноябрь': 11, 'Декабрь': 12}
month = Combobox(window, values=month_dict.keys, state="readonly", width=10)
month.current(6)
month.place(x=110, y=50)
#month_value = month.get()

# создание поля для ввода года
#default = StringVar(window, value=1410)
#year = Entry(window, textvariable=default, width=7)
#year.place(x=250, y=47)
#year_value = year.get()

# Кнопка запуска алгоритма
btn = Button(window, text='Узнать', command=clicked)
btn.grid(column=1, row=0)
btn.place(x=30, y=100)


window.mainloop()
