# mailbox_cli
Целью проекта является создание консольного локального "почтового клиента" с возможностями отправки и удаления писем, поиска писем по ID, получателю, отправителю итд.  
Функционал реализован за счет создания двух вспомогательных файлов "битовой карты" где расположению бита соответствует номер письма(0 - письмо удалено, 1 - письмо существует) и "Базы данных писем", где каждая строка соответствует порядковому номеру в битовой карте (поля получатель, отправитель, текст и сообщения разделены с помощью символа ";".
<p align="center">
  <img src="https://i.imgur.com/0aUbPqS.png" alt="application" width="600" />
