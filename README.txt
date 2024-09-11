Funções
void create_table()

    Descrição: Cria uma nova tabela. Solicita o nome da tabela, o número de colunas, e o nome e tipo de cada coluna. Define a chave primária e verifica se é válida (deve ser do tipo int).
    Requisitos: Nenhum.

void list_tables()

    Descrição: Lista todas as tabelas existentes.
    Requisitos: Nenhum.

void insert_into_table()

    Descrição: Insere um novo registro em uma tabela existente. Solicita o nome da tabela e os valores para cada coluna. Verifica se a chave primária já existe para evitar duplicatas.
    Requisitos: O arquivo da tabela deve estar acessível para leitura e escrita.

void list_table_data()

    Descrição: Lista todos os dados de uma tabela específica.
    Requisitos: O arquivo da tabela deve estar acessível para leitura.

void search_table()

    Descrição: Pesquisa registros em uma tabela com base em um valor específico para uma coluna selecionada.
    Requisitos: O arquivo da tabela deve estar acessível para leitura.

void delete_record()

    Descrição: Apaga um registro de uma tabela com base no valor da chave primária. Utiliza um arquivo temporário para reescrever o conteúdo sem o registro a ser excluído.
    Requisitos: O arquivo da tabela deve estar acessível para leitura e escrita. Deve haver permissão para criar e deletar arquivos.

void delete_table()

    Descrição: Apaga uma tabela e seu arquivo correspondente. Atualiza a lista de tabelas no arquivo de persistência.
    Requisitos: O arquivo da tabela deve estar acessível para deleção.

void load_tables()

    Descrição: Carrega a lista de tabelas a partir do arquivo binário tables_list.dat.
    Requisitos: O arquivo tables_list.dat deve existir e estar formatado corretamente.

void save_tables()

    Descrição: Salva a lista atual de tabelas no arquivo binário tables_list.dat.
    Requisitos: Permissões para escrita no arquivo tables_list.dat.

Arquivos

    tables_list.dat: Arquivo binário que armazena a lista de tabelas, incluindo seus nomes, número de colunas e detalhes das colunas.
    Arquivo de tabela (.dat): Arquivo de texto para cada tabela, onde cada linha representa um registro com valores separados por espaços.

Considerações

    Foi um  ótimo trabalho coletivo, acabou juntos fizemos todas as funções, por que quando um sentia dificuldade o outro ajudava, conseguimos fazer todas as funções do projeto,
    sentimos dificuldade principalmente na implementação de arquivos e a validação do ID, mas no final acabou dando tudo certo.
    
Como compilar

    Simplismente ter um Vscode ou usar o Replit, e da run, que os arquivos e as informações sao salvas automaticamente e cria na sua maquina um arquivo com as informações.

O que faria diferente

    Siceramente eu achei o projeto com uma dificuldade enorme para realizar e por causa do atrado da greve, começou um curso que eu tinha pago no começo do ano(o Curso iria começar exatamente 2 semanas após o fim do primeiro semestre normal),
    então foi bem dificil, para melhorar  acho que o professor poderia sugerir videos especificos e documentos para auxiliar na criação do projeto, pois procurei muitooo
    e a maioria das coisas não ajudavam muito ou utilizavam outras liguagens ou não tinha nada haver com o projeto.

